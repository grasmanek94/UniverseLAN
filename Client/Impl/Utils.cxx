#include "Utils.hxx"

namespace galaxy
{
	namespace api
	{
		Utils::~Utils()
		{
		}

		void Utils::GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) {

		}

		void Utils::GetImageRGBA(uint32_t imageID, void* buffer, uint32_t bufferLength) {

		}

		void Utils::RegisterForNotification(const char* type) {

		}

		uint32_t Utils::GetNotification(NotificationID notificationID, bool& consumable, char* type, uint32_t typeLength, void* content, uint32_t contentSize) {
			return 0;
		}

		void Utils::ShowOverlayWithWebPage(const char* url) {

		}

		bool Utils::IsOverlayVisible() {
			return false;
		}

		OverlayState Utils::GetOverlayState() {
			return OVERLAY_STATE_DISABLED;
		}

		void Utils::DisableOverlayPopups(const char* popupGroup) {

		}

		GogServicesConnectionState Utils::GetGogServicesConnectionState() {
			return GOG_SERVICES_CONNECTION_STATE_CONNECTED;
		}
	}
}


