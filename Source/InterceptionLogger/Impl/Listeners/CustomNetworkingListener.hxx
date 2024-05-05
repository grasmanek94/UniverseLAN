#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

#include <ICustomNetworking.h>

namespace universelan::client {
	using namespace galaxy::api;

	class ConnectionOpenListener : public IConnectionOpenListener
	{
	public:
		virtual void OnConnectionOpenSuccess(const char* connectionString, ConnectionID connectionID);
		virtual void OnConnectionOpenFailure(const char* connectionString, FailureReason failureReason);
	};

	class ConnectionCloseListener : public IConnectionCloseListener
	{
	public:
		virtual void OnConnectionClosed(ConnectionID connectionID, CloseReason closeReason);
	};

	class ConnectionDataListener : public IConnectionDataListener
	{
	public:
		virtual void OnConnectionDataReceived(ConnectionID connectionID, uint32_t dataSize);
	};
}

#endif
