#pragma once
#include <IListenerRegistrar.h>

#include <functional>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
		static ProxifySyncHandler instance{};
		return &instance;
	}

	static void add(galaxy::api::IGalaxyListener* proxy, galaxy::api::IGalaxyListener* real);
	static std::vector<galaxy::api::IGalaxyListener*> pop_proxies_from_real(galaxy::api::IGalaxyListener* real);
	static galaxy::api::IGalaxyListener* pop_real_from_proxy(galaxy::api::IGalaxyListener* proxy);

	static void delete_protection_enable(galaxy::api::IGalaxyListener* proxy);
	static bool is_delete_protection_enabled(galaxy::api::IGalaxyListener* proxy);
	static bool delete_if_not_protected(galaxy::api::IGalaxyListener* proxy);
	static void delete_protection_disable(galaxy::api::IGalaxyListener* proxy);
};

#define IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(class_type, listener_type) \
public: \
	inline class_type() : target{nullptr} {} \
	static inline listener_type* encapsulate(listener_type* listener) \
	{ \
		if (!listener) { \
			return nullptr; \
		} \
		class_type* proxy = new class_type(); \
		proxy->target = listener; \
		ProxifySyncHandler::add(proxy, proxy->target); \
		return proxy; \
	} \
private: \
	listener_type* target

#define IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(func) \
	do { /* Explicit contract that IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC MUST be the LAST instruction in a callback */ \
		if (target) { \
			trace.write_all("listener: {}", (void*)target); \
			ProxifySyncHandler::delete_protection_enable(this); \
			target->func; \
			ProxifySyncHandler::delete_protection_disable(this); \
			ProxifySyncHandler::pop_real_from_proxy(this); \
			delete this; \
		} \
		return; \
	} \
	while(false)
