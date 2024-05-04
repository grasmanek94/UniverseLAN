#include "ListenerRegistrar.hxx"

#include <Tracer.hxx>
#include <GalaxyDLL.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;
	ListenerRegistrarImpl::ListenerRegistrarImpl(InterfaceInstances* intf)
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };
	}

	ListenerRegistrarImpl::~ListenerRegistrarImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };
	}

	void ListenerRegistrarImpl::Register(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_HAS_LISTENERTYPE
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name(listenerType)));
#else
			trace.write_all(std::format("listenerType: {}", listenerType));
#endif
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		RealGalaxyDLL_ListenerRegistrar()->Register(listenerType, listener);
	}

	void ListenerRegistrarImpl::Unregister(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::LISTENERREGISTRAR };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_HAS_LISTENERTYPE
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name(listenerType)));
#else
			trace.write_all(std::format("listenerType: {}", listenerType));
#endif
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		RealGalaxyDLL_ListenerRegistrar()->Unregister(listenerType, listener);
	}
}
