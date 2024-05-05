#include "ListenerRegistrar.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::LISTENERREGISTRAR;
	}

	ListenerRegistrarImpl::ListenerRegistrarImpl(FuncT::F intf) : intf{ intf } {}
	ListenerRegistrarImpl::~ListenerRegistrarImpl() {}

	void ListenerRegistrarImpl::Register(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_HAS_LISTENERTYPE
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name(listenerType)));
#else
			trace.write_all(std::format("listenerType: {}", listenerType));
#endif
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->Register(listenerType, listener);
	}

	void ListenerRegistrarImpl::Unregister(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_HAS_LISTENERTYPE
			trace.write_all(std::format("listenerType: {}", magic_enum::enum_name(listenerType)));
#else
			trace.write_all(std::format("listenerType: {}", listenerType));
#endif
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->Unregister(listenerType, listener);
	}
}
