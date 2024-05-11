#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IUTILS

#include "ProxifySingleShotListener.hxx"

#include <IUtils.h>

namespace universelan::client {
	using namespace galaxy::api;

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	class OverlayVisibilityChangeListener : public IOverlayVisibilityChangeListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(OverlayVisibilityChangeListener, IOverlayVisibilityChangeListener);

	public:
		virtual void OnOverlayVisibilityChanged(bool overlayVisible);
	};

	class OverlayInitializationStateChangeListener : public IOverlayInitializationStateChangeListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(OverlayInitializationStateChangeListener, IOverlayInitializationStateChangeListener);

	public:
		virtual void OnOverlayStateChanged(OverlayState overlayState);
	};
#endif

	class NotificationListener : public INotificationListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(NotificationListener, INotificationListener);

	public:
		virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize);
	};

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	class GogServicesConnectionStateListener : public IGogServicesConnectionStateListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(GogServicesConnectionStateListener, IGogServicesConnectionStateListener);

	public:
		virtual void OnConnectionStateChange(GogServicesConnectionState connectionState);
	};
#endif
}

#endif
