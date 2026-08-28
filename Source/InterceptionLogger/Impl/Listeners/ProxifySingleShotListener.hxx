#pragma once
#include <IListenerRegistrar.h>

#include <mutex>
#include <unordered_map>
#include <unordered_set>

class ProxifySyncHandler {
public:
	using mutex_t = std::recursive_mutex;
	using lock_t = std::scoped_lock<mutex_t>;

private:
	mutex_t mtx_proxify;
	std::unordered_map<galaxy::api::IGalaxyListener*, galaxy::api::IGalaxyListener*> proxify;

	mutex_t mtx_proxify_protected;
	std::unordered_set<galaxy::api::IGalaxyListener*> proxify_protected;

	ProxifySyncHandler();

public:
	static ProxifySyncHandler* get() {
		static ProxifySyncHandler instance;
		return &instance;
	}

	static void add(galaxy::api::IGalaxyListener* real, galaxy::api::IGalaxyListener* proxy);
	static galaxy::api::IGalaxyListener* pop(galaxy::api::IGalaxyListener* real);

	static void delete_protection_enable(galaxy::api::IGalaxyListener* proxy);
	static bool is_delete_protection_enabled(galaxy::api::IGalaxyListener* proxy);
	static void delete_protection_disable(galaxy::api::IGalaxyListener* proxy);
};

// REVIEW: Encapsulation stores only a raw target pointer and gives the SDK a heap proxy; no
// ownership or unregister hook keeps either object alive. An async callback after the caller
// destroys the target therefore dereferences freed storage. Make target lifetime explicit.
// The persistent listeners created by ListenersContainer have a null target and do not enter
// this path; this concern applies to operation-specific proxies.
#define IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(class_type, listener_type) \
public: \
	inline class_type() : target{nullptr}, proxify_unregister_delete_protection{false} {} \
	static inline listener_type* encapsulate(listener_type* listener) \
	{ \
		if (!listener) { \
			return nullptr; \
		} \
		class_type* proxy = new class_type(); \
		proxy->target = listener; \
		ProxifySyncHandler::add(proxy->target, proxy); \
		return proxy; \
	} \
private: \
	listener_type* target; \
	bool proxify_unregister_delete_protection

// REVIEW: This is single-shot cleanup: it deletes the proxy after a normal callback without
// unregistering it. Keep this macro restricted to SDK operations whose listener lifetime ends
// after one callback, or unregister before destruction for a persistent registration.
// REVIEW: Cleanup is not exception-safe: an exception from target->func skips disable/pop/delete,
// leaving protection enabled and the proxy/map entry live. Guard cleanup with RAII and contain
// exceptions at the ABI boundary.
// REVIEW: target->func runs before the map entry is removed and this is deleted. If the target
// synchronously causes this same proxy to be called again, the nested call can delete this and
// the outer call then deletes it again. Defer destruction until all in-flight callbacks return.
#define IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(func) \
	if (target) { \
		trace.write_all(std::format("listener: {}", (void*)target)); \
		ProxifySyncHandler::delete_protection_enable(this); \
		target->func; \
		ProxifySyncHandler::delete_protection_disable(this); \
		ProxifySyncHandler::pop(target); \
		delete this; \
	}
