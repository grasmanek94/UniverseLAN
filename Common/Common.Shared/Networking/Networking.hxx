#pragma once

#ifdef _WIN32
#include <concurrent_queue.h>
#endif

#include <cstdlib>
#include <enet/enetpp.hxx>
#include <memory>
#include <atomic>
#include "Messages.hxx"

class MessageReceiver
{
public:
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) = 0;

	virtual void Handle(ENetPeer* peer, const std::shared_ptr<PeerConnected>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<PeerDisconnected>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<PlayerJoin>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<PlayerQuit>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<PlayerSpawn>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<PlayerDespawn>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<OnFootSync>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<WorldUpdate>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<GameSetup>& data) = 0;
public:
	template <size_t unused = 0>
	bool ProcessEvent(const ENetEvent& event, std::vector<size_t> class_list = {})
	{
		bool return_value = false;

		switch(event.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
			{
				//Handle packet
				ENetPacket* packet = event.packet;
				bool processed_packet = true;
				if (packet->dataLength >= sizeof(size_t))
				{
					size_t unique_class_id = (*reinterpret_cast<size_t*>(packet->data));

					#define IMPLEMENT_CASE_FOR(class_name) \
						case class_name::UniqueClassId(): \
						{ \
							bool errorOccured = false; \
							std::shared_ptr<class_name> var(std::make_shared<class_name>()); \
							std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary); \
							\
							if (packet->dataLength > sizeof(size_t)) \
							{ \
								stream.write(reinterpret_cast<char*>(packet->data + sizeof(size_t)), packet->dataLength - sizeof(size_t)); \
							} \
							\
							try \
							{ \
								cereal::BinaryInputArchive iarchive(stream); \
								iarchive(*var); \
							} \
							catch (const std::exception&) \
							{ \
								errorOccured = true; \
							} \
							\
							if (!errorOccured) \
							{ \
								Handle(event.peer, var); \
								return_value = true; \
							} \
						} \
						break;

					#pragma warning( push )
					#pragma warning( disable : 4307 )

					bool process_this_case;

					if (class_list.size())
					{
						process_this_case = false;
						for (auto& class_id : class_list)
						{
							if (class_id == unique_class_id)
							{
								process_this_case = true;
								break;
							}
						}
					}
					else
					{
						process_this_case = true;
					}

					if (process_this_case)
					{
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
					}
					else
					{
						processed_packet = false;
					}

					#pragma warning( pop )

					#undef IMPLEMENT_CASE_FOR

				}

				if (processed_packet)
				{
					/* Clean up the packet now that we're done using it. */
					enet_packet_destroy(event.packet);
				}
				break;
			}

			case ENET_EVENT_TYPE_CONNECT:
			{
				bool process_this_case;

				if (class_list.size())
				{
					process_this_case = false;
					for (auto& class_id : class_list)
					{
						if (class_id == EventConnect::UniqueClassId())
						{
							process_this_case = true;
							break;
						}
					}
				}
				else
				{
					process_this_case = true;
				}

				if (process_this_case)
				{
					Handle(event.peer, std::make_shared<EventConnect>(event.peer));
					return_value = true;
				}
				break;
			}
				
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				bool process_this_case;

				if (class_list.size())
				{
					process_this_case = false;
					for (auto& class_id : class_list)
					{
						if (class_id == EventDisconnect::UniqueClassId())
						{
							process_this_case = true;
							break;
						}
					}
				}
				else
				{
					process_this_case = true;
				}

				if (process_this_case)
				{
					Handle(event.peer, std::make_shared<EventDisconnect>(event.peer));
					return_value = true;
				}
				break;
			}

			case ENET_EVENT_TYPE_NONE:
				//no warnings plz
				return_value = true;
				break;

		}
		return return_value;
	}
};

template<typename T>
ENetPacket* ConvertToENetPacket(const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
{
	/*
	Well reduced it to double-buffer, I think we're not going to get any faster with this
	*/
	std::stringstream ss(std::ios::in | std::ios::out | std::ios::binary);
	size_t unique_id = object->UniqueClassId();
	ss.write(reinterpret_cast<char*>(&unique_id), sizeof(size_t));
	cereal::BinaryOutputArchive oarchive(ss);
	oarchive(*object);

	size_t x = ss.tellp();

	ENetPacket* packet = enet_packet_create(nullptr, x, flags);

	if (!packet)
	{
		return nullptr;
	}

	ss.rdbuf()->sgetn(reinterpret_cast<char*>(packet->data), x);

	return packet;
}

template<typename T>
ENetPacket* ConvertToENetPacket(const T& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
{
	/*
	Well reduced it to double-buffer, I think we're not going to get any faster with this
	*/
	std::stringstream ss(std::ios::in | std::ios::out | std::ios::binary);
	size_t unique_id = object.UniqueClassId();
	ss.write(reinterpret_cast<char*>(&unique_id), sizeof(size_t));
	cereal::BinaryOutputArchive oarchive(ss);
	oarchive(object);

	size_t x = ss.tellp();

	ENetPacket* packet = enet_packet_create(nullptr, x, flags);

	if(!packet)
	{ 
		return nullptr;
	}

	ss.rdbuf()->sgetn(reinterpret_cast<char*>(packet->data), x);

	return packet;
}

class V_Plus_NetworkClient : public NetworkClient
{

private:
	Concurrency::concurrent_queue<ENetPacket*> delayed_packets_to_send;
	Concurrency::concurrent_queue<ENetEvent> received_events_to_process;
public:
	template<typename T>
	bool SendAsync(const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(*object, flags);

		if (!packet)
		{
			return false;
		}

		delayed_packets_to_send.push(packet);
		return true;
	}

	template<typename T>
	bool SendAsync(const T& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(object, flags);

		if (!packet)
		{
			return false;
		}

		delayed_packets_to_send.push(packet);
		return true;
	}

	void RunNetworking();
	void ProcessEvents(MessageReceiver* receiver, std::vector<size_t> class_list = {});
private:
	std::atomic<bool> is_active;
public:
	void SetActive(bool active);
	bool IsActive();

	V_Plus_NetworkClient();
};

class V_Plus_NetworkServer : public NetworkServer
{
public:
	template<typename T>
	int Send(ENetPeer* peer, const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(*object, flags);

		if (!packet)
		{
			return -1;
		}

		return NetworkServer::Send(peer, packet);
	}

	template<typename T>
	int Send(ENetPeer* peer, const T& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(object, flags);

		if (!packet)
		{
			return -1;
		}

		return NetworkServer::Send(peer, packet);
	}

	template<typename T>
	bool Broadcast(const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(*object, flags);

		if (!packet)
		{
			return false;
		}

		NetworkServer::Broadcast(packet);
		return true;
	}

	template<typename T>
	bool Broadcast(const T& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(object, flags);

		if (!packet)
		{
			return false;
		}

		NetworkServer::Broadcast(packet);
		return true;
	}


	template<typename T>
	bool Broadcast(const std::shared_ptr<T>& object, ENetPeer* except, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(*object, flags);

		if (!packet)
		{
			return false;
		}

		NetworkServer::Broadcast(packet, except);
		return true;
	}

	template<typename T>
	bool Broadcast(const T& object, ENetPeer* except, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		ENetPacket* packet = ConvertToENetPacket(object, flags);

		if (!packet)
		{
			return false;
		}

		NetworkServer::Broadcast(packet, except);
		return true;
	}
};
