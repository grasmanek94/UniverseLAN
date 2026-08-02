#include "Networking.hxx"

#include <chrono>
#include <functional>

namespace universelan {
	namespace {
		struct Finally {
				std::function<void()> f;
				~Finally() { f(); }
		};
	}

	bool MessageReceiver::ProcessEvent(const ENetEvent& event)
	{
		bool return_value = false;

		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
		{
			//Handle packet
			ENetPacket* packet = event.packet;
			auto cleanup = [&]() {
				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy(event.packet);
			};

			Finally guard{ cleanup };

			if (packet->dataLength >= sizeof(uint64_t))
			{
				uint64_t unique_class_id = 0;
				bool got_unique_class_id{ false };

				try
				{
					boost::iostreams::array_source source(
						reinterpret_cast<const char*>(packet->data),
						packet->dataLength);

					boost::iostreams::stream<boost::iostreams::array_source> stream(source);

					cereal::PortableBinaryInputArchive iarchive(stream);

					// Get the class ID
					iarchive(unique_class_id);

					got_unique_class_id = true;
				}
				catch (const std::exception&)
				{
					return_value = false;
				}

				if (got_unique_class_id)
				{
					// VVV PROCESS EVENT PACKET VVV
#define SHARED_NETWORK_IMPLEMENT_CASE_FOR(class_name) \
				case class_name::UniqueClassId(): { return_value = ProcessEventFor<class_name>(event); } break

#pragma warning( push )
#pragma warning( disable : 4307 )

					switch (unique_class_id)
					{
						SHARED_NETWORK_IMPLEMENT_ALL_CASES();

					default:
						return_value = false;
						break;
					}

#pragma warning( pop )

#undef SHARED_NETWORK_IMPLEMENT_CASE_FOR
					// ^^^ PROCESS EVENT PACKET ^^^
				}
			}

			break;
		}

		case ENET_EVENT_TYPE_CONNECT:
		{
			Handle(event.peer, std::make_shared<EventConnect>());
			return_value = true;
			break;
		}

		case ENET_EVENT_TYPE_DISCONNECT:
		{
			Handle(event.peer, std::make_shared<EventDisconnect>());
			return_value = true;
			break;
		}

		case ENET_EVENT_TYPE_NONE:
			//no warnings plz
			return_value = true;
			break;

		}
		return return_value;
	}

	void GalaxyNetworkClient::CheckSendPing()
	{
		if (network_timeout != duration_t::zero())
		{
			auto now = steady_clock_t::now();
			if (now > next_ping_time)
			{
				next_ping_time = now + calculated_ping_delay;

				PingMessage message{ static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()) };
				SendAsync(message, (ENetPacketFlag)(ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT | ENET_PACKET_FLAG_UNSEQUENCED));
			}
		}
	}

	void GalaxyNetworkClient::DispatchQueuedPackets()
	{
		ENetPacket* packet = nullptr;
		while (delayed_packets_to_send.try_pop(packet))
		{
			if (NetworkClient::Send(packet) != 0)
			{
				enet_packet_destroy(packet);
			}
		}
	}

	GalaxyNetworkClient::RunNetworkingResult GalaxyNetworkClient::RunNetworking(uint32_t timeout)
	{
		GalaxyNetworkClient::RunNetworkingResult result = GalaxyNetworkClient::RunNetworkingResult::NONE;

		CheckSendPing();
		DispatchQueuedPackets();

		bool disconnected{ false };
		bool reconnect{ false };
		auto now = steady_clock_t::now();

		if (NetworkClient::Pull(timeout))
		{
			ENetEvent event = NetworkClient::Event();
			if (event.type != ENET_EVENT_TYPE_NONE)
			{
				if (event.type == ENET_EVENT_TYPE_CONNECT) {
					is_connected = true;
					next_reconnect_time.reset();
					next_ping_time = now + calculated_ping_delay;

					result = GalaxyNetworkClient::RunNetworkingResult::CONNECTED_EVENT;
				}
				else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
					is_connected = false;
					disconnected = true;
					
					result = GalaxyNetworkClient::RunNetworkingResult::DISCONNECTED_EVENT;
				}

				received_events_to_process.push(event);

				last_network_activity = std::chrono::steady_clock::now();
			}
		}

		if (!disconnected && 
			is_connected && 
			(network_timeout != duration_t::zero()))
		{
			auto inactivity_time = now - last_network_activity;

			if (inactivity_time > network_timeout)
			{
				is_connected = false;
				disconnected = true;

				result = GalaxyNetworkClient::RunNetworkingResult::DISCONNECTED_TIMEOUT;
			}
		}

		if (disconnected) {
			Cleanup();

			reconnect = true;

			ENetEvent event = NetworkClient::Event();
			event.type = ENET_EVENT_TYPE_DISCONNECT;
			received_events_to_process.push(event);
		}

		if (next_reconnect_time.has_value() && (now > next_reconnect_time.value()))
		{
			reconnect = true;
		}

		if (reconnect)
		{
			if (network_timeout != duration_t::zero())
			{
				next_reconnect_time = now + (network_timeout * RECONNECT_NETWORK_TIMEOUT_FACTOR);
			}
			Reconnect();
		}

		return result;
	}

	void GalaxyNetworkClient::ProcessEvents(MessageReceiver* receiver)
	{
		ENetEvent event;

		while (received_events_to_process.try_pop(event))
		{
			receiver->ProcessEvent(event);
		}
	}

	bool GalaxyNetworkClient::IsConnected() const {
		return is_connected;
	}

	GalaxyNetworkClient::GalaxyNetworkClient() :
		is_connected{ false }, is_timeout{ false }, 
		last_network_activity{ steady_clock_t::now() },
		next_ping_time{ steady_clock_t::now() },
		next_reconnect_time{ },
		network_timeout{ duration_t::zero() },
		calculated_ping_delay{ duration_t::zero() }
	{}


	GalaxyNetworkClient::~GalaxyNetworkClient() {
		Cleanup();
	}

	void GalaxyNetworkClient::Cleanup() {
		ENetEvent event{};
		while (!received_events_to_process.empty()) {
			if (received_events_to_process.try_pop(event)) {
				if (event.type == ENET_EVENT_TYPE_RECEIVE) {
					enet_packet_destroy(event.packet);
				}
			}
		}

		ENetPacket* packet = nullptr;
		while (!delayed_packets_to_send.empty()) {
			if (delayed_packets_to_send.try_pop(packet)) {
				enet_packet_destroy(packet);
			}
		}
	}

	void GalaxyNetworkClient::SetNetworkReconnectTimeout(const GalaxyNetworkClient::duration_t& duration)
	{
		network_timeout = duration;
		calculated_ping_delay = (network_timeout / AMOUNT_OF_PINGS_IN_TIMEOUT_DURATION);
	}
}
