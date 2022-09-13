#pragma once

#include <enet/enetpp.hxx>

#include "Messages.hxx"

#ifdef _WIN32
#include <concurrent_queue.h>
#endif

#include <cstdlib>
#include <memory>
#include <atomic>

class MessageReceiver
{
public:
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) = 0;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) = 0;

	virtual void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& data) = 0;

	template <typename T>
	bool ProcessEventFor(const ENetEvent& event) {
		static_assert(T::UniqueClassId, "T must implement UniqueClassId");

		//Handle packet
		ENetPacket* packet = event.packet;
		if (packet->dataLength >= sizeof(uint64_t))
		{
			uint64_t unique_class_id = (*reinterpret_cast<uint64_t*>(packet->data));

			if (unique_class_id == T::UniqueClassId()) {

				std::shared_ptr<T> var(std::make_shared<T>());

				if (packet->dataLength > sizeof(uint64_t))
				{
					bool errorOccured = false;

					std::stringstream stream(std::ios::in | std::ios::out | std::ios::binary);

					stream.write(reinterpret_cast<char*>(packet->data + sizeof(uint64_t)), packet->dataLength - sizeof(uint64_t));

					try
					{
						cereal::BinaryInputArchive iarchive(stream);
						iarchive(*var);

					}
					catch (const std::exception&)
					{
						errorOccured = true;
					}

					if (!errorOccured) {
						Handle(event.peer, var);
					}
				} else {
					Handle(event.peer, var);
					return true;
				}
			}
		}

		return false;
	}

	bool ProcessEvent(const ENetEvent& event);

	virtual ~MessageReceiver() {}
};

template<typename T>
ENetPacket* ConvertToENetPacket(const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
{
	/*
	Well reduced it to double-buffer, I think we're not going to get any faster with this
	*/
	std::stringstream ss(std::ios::in | std::ios::out | std::ios::binary);
	uint64_t unique_id = object->UniqueClassId();
	ss.write(reinterpret_cast<char*>(&unique_id), sizeof(uint64_t));
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
	uint64_t unique_id = object.UniqueClassId();
	ss.write(reinterpret_cast<char*>(&unique_id), sizeof(uint64_t));
	cereal::BinaryOutputArchive oarchive(ss);
	oarchive(object);

	size_t x = ss.tellp();

	ENetPacket* packet = enet_packet_create(nullptr, x, flags);

	if (!packet)
	{
		return nullptr;
	}

	ss.rdbuf()->sgetn(reinterpret_cast<char*>(packet->data), x);

	return packet;
}

class GalaxyNetworkClient : public NetworkClient
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

	void RunNetworking(uint32_t timeout);
	void ProcessEvents(MessageReceiver* receiver);
private:
	std::atomic<bool> is_active;
public:
	void SetActive(bool active);
	bool IsActive();

	GalaxyNetworkClient();

	virtual ~GalaxyNetworkClient() {}
};

class GalaxyNetworkServer : public NetworkServer
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

	virtual ~GalaxyNetworkServer() {}
};
