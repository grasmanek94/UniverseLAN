#pragma once

#include "TestCaseClientDetails.hxx"

class NetworkingListenerImplGlobal : public galaxy::api::GlobalNetworkingListener
{
public:
	using on_p2_p_packet_available_func_t = std::function<void(uint32_t, uint8_t)>;

private:
	on_p2_p_packet_available_func_t on_p2_p_packet_available;

public:
	NetworkingListenerImplGlobal(
		on_p2_p_packet_available_func_t on_p2_p_packet_available = nullptr) :
		on_p2_p_packet_available{ on_p2_p_packet_available } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~NetworkingListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"msgSize: {} channel: {}",
			msgSize, channel
		).c_str());


		if (on_p2_p_packet_available != nullptr) {
			on_p2_p_packet_available(msgSize, channel);
		}
	}
};

class NetworkingListenerImplLocal : public galaxy::api::INetworkingListener
{
public:
	using on_p2_p_packet_available_func_t = std::function<void(uint32_t, uint8_t)>;

private:
	on_p2_p_packet_available_func_t on_p2_p_packet_available;

public:
	NetworkingListenerImplLocal(
		on_p2_p_packet_available_func_t on_p2_p_packet_available = nullptr) :
		on_p2_p_packet_available{ on_p2_p_packet_available } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~NetworkingListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"msgSize: {} channel: {}",
			msgSize, channel
		).c_str());


		if (on_p2_p_packet_available != nullptr) {
			on_p2_p_packet_available(msgSize, channel);
		}
	}
};

#if GALAXY_BUILD_FEATURE_HAS_GAMESERVERNETWORKINGLISTENER

class GameServerNetworkingListenerImplGlobal : public galaxy::api::GameServerGlobalNetworkingListener
{
public:
	using on_p2_p_packet_available_func_t = std::function<void(uint32_t, uint8_t)>;

private:
	on_p2_p_packet_available_func_t on_p2_p_packet_available;

public:
	GameServerNetworkingListenerImplGlobal(
		on_p2_p_packet_available_func_t on_p2_p_packet_available = nullptr) :
		on_p2_p_packet_available{ on_p2_p_packet_available } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerNetworkingListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"msgSize: {} channel: {}",
			msgSize, channel
		).c_str());


		if (on_p2_p_packet_available != nullptr) {
			on_p2_p_packet_available(msgSize, channel);
		}
	}
};

#endif
