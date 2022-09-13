#include "Utils.hxx"

namespace galaxy
{
	namespace api
	{
		UtilsImpl::~UtilsImpl()
		{
		}

		void UtilsImpl::GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) {

		}

		void UtilsImpl::GetImageRGBA(uint32_t imageID, void* buffer, uint32_t bufferLength) {

		}

		void UtilsImpl::RegisterForNotification(const char* type) {

		}

		uint32_t UtilsImpl::GetNotification(NotificationID notificationID, bool& consumable, char* type, uint32_t typeLength, void* content, uint32_t contentSize) {
			return 0;
		}

		void UtilsImpl::ShowOverlayWithWebPage(const char* url) {

		}

		bool UtilsImpl::IsOverlayVisible() {
			return false;
		}

		OverlayState UtilsImpl::GetOverlayState() {
			return OVERLAY_STATE_DISABLED;
		}

		void UtilsImpl::DisableOverlayPopups(const char* popupGroup) {

		}

		GogServicesConnectionState UtilsImpl::GetGogServicesConnectionState() {
			return GOG_SERVICES_CONNECTION_STATE_CONNECTED;
		}
	}
}
