#include "Utils.hxx"
#include "UniverseLAN.hxx"

namespace universelan::client {
	using namespace galaxy::api;
	UtilsImpl::UtilsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() }
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	UtilsImpl::~UtilsImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	void UtilsImpl::GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) {
		tracer::Trace trace{ __FUNCTION__ };

		width = 0;
		height = 0;
	}

	void UtilsImpl::GetImageRGBA(uint32_t imageID, void* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };
	}

	void UtilsImpl::RegisterForNotification(const char* type) {
		tracer::Trace trace{ __FUNCTION__ };
	}

	uint32_t UtilsImpl::GetNotification(NotificationID notificationID
#if (GALAXY_VERSION) > 112400
		, bool& consumable
#endif
		, char* type, uint32_t typeLength, void* content, uint32_t contentSize) {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void UtilsImpl::ShowOverlayWithWebPage(const char* url) {
		tracer::Trace trace{ __FUNCTION__ };

		std::cout << "ShowOverlayWithWebPage:\n\t";
		std::cout << url << std::endl;
	}

	bool UtilsImpl::IsOverlayVisible() {
		tracer::Trace trace{ __FUNCTION__ };

		return false;
	}

	OverlayState UtilsImpl::GetOverlayState() {
		tracer::Trace trace{ __FUNCTION__ };

		return OVERLAY_STATE_DISABLED;
	}

	void UtilsImpl::DisableOverlayPopups(const char* popupGroup) {
		tracer::Trace trace{ __FUNCTION__ };
	}

#if (GALAXY_VERSION) > 112400
	GogServicesConnectionState UtilsImpl::GetGogServicesConnectionState() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->client->IsConnected() ?
			GOG_SERVICES_CONNECTION_STATE_CONNECTED :
			GOG_SERVICES_CONNECTION_STATE_DISCONNECTED;
	}
#endif

	void UtilsImpl::ConnectionStateChangeReceived(bool connected) {
		tracer::Trace trace{ __FUNCTION__ };
#if (GALAXY_VERSION) > 112400
		listeners->NotifyAll(&IGogServicesConnectionStateListener::OnConnectionStateChange,
			(connected ?
				GOG_SERVICES_CONNECTION_STATE_CONNECTED :
				GOG_SERVICES_CONNECTION_STATE_DISCONNECTED)
		);
#endif
	}
}
