#pragma once

#include <enet6/enetpp.hxx>

#include <ConcurrentQueue.hxx>
#include <MemoryInputStream.hxx>

#include "Messages.hxx"

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <utility>

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

			uint64_t unique_class_id = 0;
			std::shared_ptr<T> var(std::make_shared<T>());

			try
			{
				MemoryInputStream source{
					reinterpret_cast<const char*>(packet->data),
					static_cast<std::size_t>(packet->dataLength)
				};

				cereal::PortableBinaryInputArchive iarchive(source.stream());

				// Get the class ID
				iarchive(unique_class_id);

				if (unique_class_id != T::UniqueClassId()) {
					return false;
				}

				// Get the struct data
				iarchive(*var);
			}
			catch (const std::exception&)
			{
				return false;
			}

			Handle(event.peer, var);
			return true;
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
		constexpr uint64_t unique_id = object.UniqueClassId();
		cereal::PortableBinaryOutputArchive oarchive(ss);
		oarchive(unique_id);
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

	class GalaxyNetworkClient : public enetpp::NetworkClient
	{
	public:
		enum class RunNetworkingResult
		{
			NONE,
			CONNECTED_EVENT,
			DISCONNECTED_EVENT,
			DISCONNECTED_TIMEOUT
		};

		using steady_clock_t = std::chrono::steady_clock;
		using timepoint_t = steady_clock_t::time_point;
		using duration_t = steady_clock_t::duration;

		static constexpr unsigned long AMOUNT_OF_PINGS_IN_TIMEOUT_DURATION = 3;
		static constexpr unsigned long RECONNECT_NETWORK_TIMEOUT_FACTOR = 2;
		static constexpr duration_t FORCE_DISCONNECT_RECONNECT_TIME = std::chrono::seconds(5);

	private:
		mutable Concurrency::concurrent_queue<ENetPacket*> delayed_packets_to_send;
		mutable Concurrency::concurrent_queue<ENetEvent> received_events_to_process;

		bool is_connected;
		bool is_timeout;

		timepoint_t last_network_activity;
		timepoint_t next_ping_time;
		std::optional<timepoint_t> next_reconnect_time;

		duration_t network_timeout;
		duration_t calculated_ping_delay;

		void Cleanup();
		void CheckSendPing();
		void DispatchQueuedPackets();

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

		RunNetworkingResult RunNetworking(uint32_t timeout);
		void ProcessEvents(MessageReceiver* receiver);
		bool IsConnected() const;
		void SetNetworkReconnectTimeout(const duration_t& duration);

		GalaxyNetworkClient();
		virtual ~GalaxyNetworkClient();
	};

	class GalaxyNetworkServer : public enetpp::NetworkServer
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
