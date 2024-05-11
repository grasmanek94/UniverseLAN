#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

#include "ProxifySingleShotListener.hxx"

#include <ICustomNetworking.h>

namespace universelan::client {
	using namespace galaxy::api;

	class ConnectionOpenListener : public IConnectionOpenListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(ConnectionOpenListener, IConnectionOpenListener);

	public:
		virtual void OnConnectionOpenSuccess(const char* connectionString, ConnectionID connectionID);
		virtual void OnConnectionOpenFailure(const char* connectionString, FailureReason failureReason);
	};

	class ConnectionCloseListener : public IConnectionCloseListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(ConnectionCloseListener, IConnectionCloseListener);

	public:
		virtual void OnConnectionClosed(ConnectionID connectionID, CloseReason closeReason);
	};

	class ConnectionDataListener : public IConnectionDataListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(ConnectionDataListener, IConnectionDataListener);

	public:
		virtual void OnConnectionDataReceived(ConnectionID connectionID, uint32_t dataSize);
	};
}

#endif
