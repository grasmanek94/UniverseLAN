#include "Networking.hxx"

void V_Plus_NetworkClient::RunNetworking()
{
	ENetPacket* packet = nullptr;
	while (delayed_packets_to_send.try_pop(packet))
	{
		NetworkClient::Send(packet);
	}

	if (NetworkClient::Pull())
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
				if (packet->dataLength >= sizeof(size_t))
				{
					size_t unique_class_id = (*reinterpret_cast<size_t*>(packet->data));

					#define IMPLEMENT_CASE_FOR(class_name) \
						case class_name::UniqueClassId(): \
						{ \
							if(class_name::CaptureWhenInactive()) \
							{ \
								received_events_to_process.push(event); \
							} \
						} \
						break;

					#pragma warning( push )
					#pragma warning( disable : 4307 )

					switch (unique_class_id)
					{
						IMPLEMENT_CASE_FOR(ChatMessage);
						IMPLEMENT_CASE_FOR(PlayerJoin);
						IMPLEMENT_CASE_FOR(PlayerQuit);
						IMPLEMENT_CASE_FOR(PlayerSpawn);
						IMPLEMENT_CASE_FOR(PlayerDespawn);
						IMPLEMENT_CASE_FOR(OnFootSync);

						//Because of this we need to impl in header, so, template:
						#ifdef VPLUS_CLIENT
						IMPLEMENT_CASE_FOR(PeerConnected);
						IMPLEMENT_CASE_FOR(PeerDisconnected);
						IMPLEMENT_CASE_FOR(GameSetup);
						IMPLEMENT_CASE_FOR(WorldUpdate);
						#endif
					}

					#pragma warning( pop )

					#undef IMPLEMENT_CASE_FOR
				}
			}
		}
	}
}

void V_Plus_NetworkClient::ProcessEvents(MessageReceiver* receiver, std::vector<size_t> class_list)
{
	ENetEvent event;
	if (class_list.size() == 0)
	{
		while (received_events_to_process.try_pop(event))
		{
			receiver->ProcessEvent(event);
		}
	}
	else
	{
		while (received_events_to_process.try_pop(event))
		{
			if (!receiver->ProcessEvent(event, class_list))
			{
				received_events_to_process.push(event);
				break;
			}
		}
	}
}

V_Plus_NetworkClient::V_Plus_NetworkClient()
	: is_active(true)
{ }

void V_Plus_NetworkClient::SetActive(bool active)
{
	is_active = active;
}

bool V_Plus_NetworkClient::IsActive()
{
	return is_active;
}
