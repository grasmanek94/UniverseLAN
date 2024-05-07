#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING

#include "TestCaseClientDetails.hxx"

class ServerNetworkingListenerImplGlobal : public galaxy::api::GlobalServerNetworkingListener
{
public:
	using on_server_p2p_packet_available_func_t = std::function<void(uint32_t msgSize, uint8_t channel)>;

private:
	on_server_p2p_packet_available_func_t on_server_p2p_packet_available;

public:
	ServerNetworkingListenerImplGlobal(
		on_server_p2p_packet_available_func_t on_server_p2p_packet_available = nullptr) :
		on_server_p2p_packet_available{ on_server_p2p_packet_available } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ServerNetworkingListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnServerP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"msgSize: {} channel: {}",
			msgSize, channel
		).c_str());


		if (on_server_p2p_packet_available != nullptr) {
			on_server_p2p_packet_available(msgSize, channel);
		}
	}
};

class ServerNetworkingListenerImplLocal : public galaxy::api::IServerNetworkingListener
{
public:
	using on_server_p2p_packet_available_func_t = std::function<void(uint32_t msgSize, uint8_t channel)>;

private:
	on_server_p2p_packet_available_func_t on_server_p2p_packet_available;

public:
	ServerNetworkingListenerImplLocal(
		on_server_p2p_packet_available_func_t on_server_p2p_packet_available = nullptr) :
		on_server_p2p_packet_available{ on_server_p2p_packet_available } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ServerNetworkingListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnServerP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"msgSize: {} channel: {}",
			msgSize, channel
		).c_str());


		if (on_server_p2p_packet_available != nullptr) {
			on_server_p2p_packet_available(msgSize, channel);
		}
	}
};

#if GALAXY_BUILD_FEATURE_HAS_GAMESERVERSERVERNETWORKINGLISTENER

class GameServerServerNetworkingListenerImplGlobal : public galaxy::api::GameServerGlobalServerNetworkingListener
{
public:
	using on_server_p2p_packet_available_func_t = std::function<void(uint32_t msgSize, uint8_t channel)>;

private:
	on_server_p2p_packet_available_func_t on_server_p2p_packet_available;

public:
	GameServerServerNetworkingListenerImplGlobal(
		on_server_p2p_packet_available_func_t on_server_p2p_packet_available = nullptr) :
		on_server_p2p_packet_available{ on_server_p2p_packet_available } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerServerNetworkingListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnServerP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"msgSize: {} channel: {}",
			msgSize, channel
		).c_str());


		if (on_server_p2p_packet_available != nullptr) {
			on_server_p2p_packet_available(msgSize, channel);
		}
	}
};

#endif
#endif
