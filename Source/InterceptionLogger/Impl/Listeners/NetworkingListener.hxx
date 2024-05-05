#pragma once

#include <INetworking.h>

namespace universelan::client {
	using namespace galaxy::api;

	class NetworkingListener : public INetworkingListener
	{
	public:
		virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel);
	};

	class NatTypeDetectionListener : public INatTypeDetectionListener
	{
	public:
		virtual void OnNatTypeDetectionSuccess(NatType natType);
		virtual void OnNatTypeDetectionFailure();
	};

}
