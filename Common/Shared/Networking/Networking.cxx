#include "Networking.hxx"

namespace universelan {
	bool MessageReceiver::ProcessEvent(const ENetEvent& event)
	{
		bool return_value = false;

		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
		{
			//Handle packet
			ENetPacket* packet = event.packet;
			if (packet->dataLength >= sizeof(uint64_t))
			{
				uint64_t unique_class_id = (*reinterpret_cast<uint64_t*>(packet->data));

#define SHARED_NETWORK_IMPLEMENT_CASE_FOR(class_name) \
					case class_name::UniqueClassId(): { return_value = ProcessEventFor<class_name>(event); } break

#pragma warning( push )
#pragma warning( disable : 4307 )

				switch (unique_class_id)
				{
					SHARED_NETWORK_IMPLEMENT_ALL_CASES();
				}

#pragma warning( pop )

#undef SHARED_NETWORK_IMPLEMENT_CASE_FOR
			}

			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy(event.packet);

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

	void GalaxyNetworkClient::RunNetworking(uint32_t timeout)
	{
		ENetPacket* packet = nullptr;
		while (delayed_packets_to_send.try_pop(packet))
		{
			NetworkClient::Send(packet);
		}

		bool disconnected{ false };
		if (NetworkClient::Pull(timeout))
		{
			ENetEvent event = NetworkClient::Event();
			if (event.type != ENET_EVENT_TYPE_NONE)
			{
				if (event.type == ENET_EVENT_TYPE_CONNECT) {
					is_connected = true;
				}
				else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
					is_connected = false;
					disconnected = true;
				}

				received_events_to_process.push(event);
			}
		}

		if (disconnected) {
			Cleanup();
		}
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
		is_connected{ false }
	{ }


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
}
