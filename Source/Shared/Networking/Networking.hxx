#pragma once

#include <enet/enetpp.hxx>

#include <ConcurrentQueue.hxx>

#include "Messages.hxx"

#include <cstdlib>
#include <memory>
#include <atomic>

namespace universelan {
	class MessageReceiver
	{
	public:
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) = 0;
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) = 0;

#include <Networking/MessageHandlersDeclarePureVirtual.hxx>

		template <typename T>
		bool ProcessEventFor(const ENetEvent& event) {
			static_assert(T::UniqueClassId, "T must implement UniqueClassId");

			//Handle packet
			ENetPacket* packet = event.packet;
			if (packet->dataLength < sizeof(uint64_t))
			{
				return false;
			}

			uint64_t unique_class_id = (*reinterpret_cast<uint64_t*>(packet->data));

			if (unique_class_id != T::UniqueClassId()) {
				return false;
			}

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
					return true;
				}
			}
			else {
				Handle(event.peer, var);
				return true;
			}

			return false;
		}

		bool ProcessEvent(const ENetEvent& event);

		virtual ~MessageReceiver() {}
	};

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

		size_t x = (size_t)ss.tellp();

		ENetPacket* packet = enet_packet_create(nullptr, x, flags); // maybe no allocate flag and the nullptr can be replaced by data somehow

		if (!packet)
		{
			return nullptr;
		}

		ss.rdbuf()->sgetn(reinterpret_cast<char*>(packet->data), x);

		return packet;
	}

	template<typename T>
	ENetPacket* ConvertToENetPacket(const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
	{
		return ConvertToENetPacket(*object, flags);
	}

	class GalaxyNetworkClient : public NetworkClient
	{
	private:
		mutable Concurrency::concurrent_queue<ENetPacket*> delayed_packets_to_send;
		mutable Concurrency::concurrent_queue<ENetEvent> received_events_to_process;

		bool is_connected;

		void Cleanup();
	public:
		template<typename T>
		bool SendAsync(const T& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE) const
		{
			ENetPacket* packet = ConvertToENetPacket(object, flags);

			if (!packet)
			{
				return false;
			}

			delayed_packets_to_send.push(packet);
			return true;
		}

		template<typename T>
		bool SendAsync(const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE) const
		{
			return SendAsync(*object, flags);
		}

		void RunNetworking(uint32_t timeout);
		void ProcessEvents(MessageReceiver* receiver);
		bool IsConnected() const;

		GalaxyNetworkClient();
		virtual ~GalaxyNetworkClient();
	};

	class GalaxyNetworkServer : public NetworkServer
	{
	public:
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
		int Send(ENetPeer* peer, const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
		{
			return Send(peer, *object, flags);
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
		bool Broadcast(const std::shared_ptr<T>& object, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
		{
			return Broadcast(*object, flags);
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


		template<typename T>
		bool Broadcast(const std::shared_ptr<T>& object, ENetPeer* except, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE)
		{
			return Broadcast(*object, except, flags);
		}

		virtual ~GalaxyNetworkServer() {}
	};
}
