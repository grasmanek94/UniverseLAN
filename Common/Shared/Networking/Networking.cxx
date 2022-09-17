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

		if (NetworkClient::Pull(timeout))
		{
			ENetEvent event = NetworkClient::Event();
			if (event.type != ENET_EVENT_TYPE_NONE)
			{
				if (IsActive() || event.type != ENET_EVENT_TYPE_RECEIVE)
				{
					received_events_to_process.push(event);
				}
				else if (!IsActive() && event.type == ENET_EVENT_TYPE_RECEIVE)
				{
					ENetPacket* packet = event.packet;
					if (packet->dataLength >= sizeof(uint64_t))
					{
						uint64_t unique_class_id = (*reinterpret_cast<uint64_t*>(packet->data));

#define SHARED_NETWORK_IMPLEMENT_CASE_FOR(class_name) \
						case class_name::UniqueClassId(): \
						{ \
							received_events_to_process.push(event); \
						} \
						break;

#pragma warning( push )
#pragma warning( disable : 4307 )

						switch (unique_class_id)
						{
							SHARED_NETWORK_IMPLEMENT_ALL_CASES();

						default:
							break;
						}

#pragma warning( pop )

#undef SHARED_NETWORK_IMPLEMENT_CASE_FOR
					}
				}
			}
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

	GalaxyNetworkClient::GalaxyNetworkClient()
		: is_active(true)
	{ }

	void GalaxyNetworkClient::SetActive(bool active)
	{
		is_active = active;
	}

	bool GalaxyNetworkClient::IsActive() const
	{
		return is_active;
	}
}
