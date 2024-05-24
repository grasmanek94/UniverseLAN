#if GALAXY_BUILD_FEATURE_HAS_IUTILS

#include "UtilsListener.hxx"
#include "ProxifySingleShotListener.hxx"

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

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	void OverlayVisibilityChangeListener::OnOverlayVisibilityChanged(bool overlayVisible)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("overlayVisible: {}", overlayVisible));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnOverlayVisibilityChanged(overlayVisible));
	}

	void OverlayInitializationStateChangeListener::OnOverlayStateChanged(OverlayState overlayState)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("overlayState: {}", magic_enum::enum_name(overlayState)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnOverlayStateChanged(overlayState));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_INOTIFICATIONLISTENER
	void NotificationListener::OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("notificationID: {}", notificationID));
			trace.write_all(std::format("typeLength: {}", typeLength));
			trace.write_all(std::format("contentSize: {}", contentSize));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnNotificationReceived(notificationID, typeLength, contentSize));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	void GogServicesConnectionStateListener::OnConnectionStateChange(GogServicesConnectionState connectionState)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionState: {}", magic_enum::enum_name(connectionState)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnConnectionStateChange(connectionState));
	}
#endif
}

#endif
