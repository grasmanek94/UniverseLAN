#if GALAXY_BUILD_FEATURE_HAS_IUTILS

#include "UtilsListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IUTILS;
	}

	void OverlayVisibilityChangeListener::OnOverlayVisibilityChanged(bool overlayVisible)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("overlayVisible: {}", overlayVisible));
		}
	}

	void OverlayInitializationStateChangeListener::OnOverlayStateChanged(OverlayState overlayState)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("overlayState: {}", magic_enum::enum_name(overlayState)));
		}
	}

	void NotificationListener::OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("notificationID: {}", notificationID));
			trace.write_all(std::format("typeLength: {}", typeLength));
			trace.write_all(std::format("contentSize: {}", contentSize));
		}
	}

	void GogServicesConnectionStateListener::OnConnectionStateChange(GogServicesConnectionState connectionState)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionState: {}", magic_enum::enum_name(connectionState)));
		}
	}
}

#endif
