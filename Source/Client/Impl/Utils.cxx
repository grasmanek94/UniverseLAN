#if GALAXY_BUILD_FEATURE_HAS_IUTILS

#include "Utils.hxx"
#include "UniverseLAN.hxx"

namespace universelan::client {
	using namespace galaxy::api;
	UtilsImpl::UtilsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() }
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
	}

	UtilsImpl::~UtilsImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
	}

	void UtilsImpl::GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		width = 0;
		height = 0;
	}

	void UtilsImpl::GetImageRGBA(uint32_t imageID, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
	}

#if GALAXY_BUILD_FEATURE_HAS_INOTIFICATIONLISTENER
	void UtilsImpl::RegisterForNotification(const char* type) {
		tracer::Trace trace { type, __FUNCTION__ };
	}


	uint32_t UtilsImpl::GetNotification(NotificationID notificationID
#if GALAXY_BUILD_FEATURE_IUTILS_GETNOTIFICATION_1_129_CHANGE
		, bool& consumable
#endif
		, char* type, uint32_t typeLength, void* content, uint32_t contentSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		return 0;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE
	void UtilsImpl::ShowOverlayWithWebPage(const char* url) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		std::cout << "ShowOverlayWithWebPage:\n\t";
		std::cout << url << std::endl;
	}
#endif

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	bool UtilsImpl::IsOverlayVisible() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		return false;
	}

	OverlayState UtilsImpl::GetOverlayState() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		return OVERLAY_STATE_DISABLED;
	}

#endif
#if GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
	void UtilsImpl::DisableOverlayPopups(const char* popupGroup) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
	}
#endif
#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	GogServicesConnectionState UtilsImpl::GetGogServicesConnectionState() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		return intf->user->IsLoggedOn() ?
			GOG_SERVICES_CONNECTION_STATE_CONNECTED :
			GOG_SERVICES_CONNECTION_STATE_DISCONNECTED;
	}
#endif

	void UtilsImpl::ConnectionStateChangeReceived(bool connected) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
		listeners->NotifyAll(&IGogServicesConnectionStateListener::OnConnectionStateChange,
			(connected ?
				GOG_SERVICES_CONNECTION_STATE_CONNECTED :
				GOG_SERVICES_CONNECTION_STATE_DISCONNECTED)
		);
#endif
	}
}

#endif
