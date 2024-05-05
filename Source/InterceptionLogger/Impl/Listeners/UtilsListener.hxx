#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IUTILS

#include <IUtils.h>

namespace universelan::client {
	using namespace galaxy::api;

	class OverlayVisibilityChangeListener : public IOverlayVisibilityChangeListener
	{
	public:
		virtual void OnOverlayVisibilityChanged(bool overlayVisible);
	};

	class OverlayInitializationStateChangeListener : public IOverlayInitializationStateChangeListener
	{
	public:
		virtual void OnOverlayStateChanged(OverlayState overlayState);
	};

	class NotificationListener : public INotificationListener
	{
	public:
		virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize);
	};

	class GogServicesConnectionStateListener : public IGogServicesConnectionStateListener
	{
	public:
		virtual void OnConnectionStateChange(GogServicesConnectionState connectionState);
	};
}

#endif
