#pragma once

#include "ProxifySingleShotListener.hxx"

#include <INetworking.h>

namespace universelan::client {
	using namespace galaxy::api;

	class NetworkingListener : public INetworkingListener
	{
	public:
		virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel);
	};

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
	class NatTypeDetectionListener : public INatTypeDetectionListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(NatTypeDetectionListener, INatTypeDetectionListener);

	public:
		virtual void OnNatTypeDetectionSuccess(NatType natType);
		virtual void OnNatTypeDetectionFailure();
	};
#endif
}
