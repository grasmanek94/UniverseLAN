#pragma once
#include <IListenerRegistrar.h>

#include <mutex>
#include <unordered_map>

class ProxifySyncHandler {
public:
	using mutex_t = std::recursive_mutex;
	using lock_t = std::scoped_lock<mutex_t>;

private:
	mutex_t mtx_proxify;
	std::unordered_map<galaxy::api::IGalaxyListener*, galaxy::api::IGalaxyListener*> proxify;

	ProxifySyncHandler();

public:
	static ProxifySyncHandler* get() {
		static ProxifySyncHandler instance;
		return &instance;
	}

	static void add(galaxy::api::IGalaxyListener* real, galaxy::api::IGalaxyListener* proxy);
	static void remove(galaxy::api::IGalaxyListener* real);
	static galaxy::api::IGalaxyListener* pop(galaxy::api::IGalaxyListener* real);
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
		ProxifySyncHandler::add(proxy->target, proxy); \
		return proxy; \
	} \
private: \
	listener_type* target

#define IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(func) \
	if (target) { \
		trace.write_all(std::format("listener: {}", (void*)target)); \
		target->func; \
		ProxifySyncHandler::remove(target); \
		delete this; \
	}
