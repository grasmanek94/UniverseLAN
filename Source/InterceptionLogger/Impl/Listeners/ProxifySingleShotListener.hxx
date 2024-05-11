#pragma once

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
		return proxy; \
	} \
private: \
	listener_type* target

#define IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(func) \
	if (target) { \
		trace.write_all(std::format("listener: {}", (void*)target)); \
		target->func; \
		delete this; \
	}
