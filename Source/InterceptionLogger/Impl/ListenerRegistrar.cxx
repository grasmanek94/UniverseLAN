#include "ListenerRegistrar.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include "Listeners/ProxifySingleShotListener.hxx"

#include <magic_enum/magic_enum.hpp>

#include <format>
#include <mutex>

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
			trace.write_all("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType));
			trace.write_all("listener: {}", (void*)listener);
		}

		intf()->Register(listenerType, listener);
	}

	void ListenerRegistrarImpl::Unregister(ListenerTypeImpl listenerType, IGalaxyListener* listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all("listenerType: {}", magic_enum::enum_name((ListenerType)listenerType));
			trace.write_all("listener: {}", (void*)listener);
		}

		auto proxies = ProxifySyncHandler::pop_proxies_from_real(listener);
		if (proxies.size()) {
			for (auto& proxy : proxies) {
				intf()->Unregister(listenerType, proxy);

				(void)ProxifySyncHandler::delete_if_not_protected(proxy);
			}
		}

		intf()->Unregister(listenerType, listener);
	}
}
