#pragma once

#include <GalaxyID.h>
#include <IMatchMaking.h>

#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <unordered_map>

namespace universelan {
	class Lobby {
	public:
		struct Message {
			uint32_t message_id;
			galaxy::api::GalaxyID sender;
			std::string data;

			template<class Archive>
			void serialize(Archive& ar)
			{
				ar(message_id, sender, data);
			}
		};

		using data_t = std::unordered_map<std::string, std::string>;
		using user_data_t = std::unordered_map<galaxy::api::GalaxyID, data_t, galaxy::api::GalaxyID::Hash>;
		using messages_t = std::map<uint32_t, Message>;
		using view_members_t = std::ranges::elements_view<
			std::ranges::ref_view<const universelan::Lobby::user_data_t>,
			0Ui64
		>;

		using data_by_index_t = std::pair<std::string, std::string>;

	private:
		galaxy::api::GalaxyID id;
		galaxy::api::GalaxyID owner_id;

		uint32_t max_members;
		bool joinable;
		galaxy::api::LobbyTopologyType topology_type;
		galaxy::api::LobbyType type;
		uint32_t current_message_id;
		data_t data;
		user_data_t user_data; // also used as members list
		messages_t messages;

	public:
		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, owner_id, max_members, joinable, 
				topology_type, type, current_message_id, 
				data, user_data, messages);
		}

		Lobby();
		Lobby(galaxy::api::GalaxyID owner_id, galaxy::api::LobbyType type, 
			uint32_t max_members, bool joinable, galaxy::api::LobbyTopologyType lobby_topology_type);
		Lobby(const Lobby& chat_room);

	private:
		static const char* GetData(const data_t& data, const char* key);
		static data_by_index_t GetDataByIndex(const data_t& data, size_t index);
		static void SetData(data_t& data, const char* key, const char* value);

	public:
		galaxy::api::LobbyTopologyType GetTopology() const;
		void SetOwner(galaxy::api::GalaxyID new_owner);
		galaxy::api::GalaxyID ChooseNewOwner();

		const view_members_t GetMembers() const;
		bool AddMember(galaxy::api::GalaxyID id);
		bool RemoveMember(galaxy::api::GalaxyID id);
		bool IsMember(galaxy::api::GalaxyID id) const;

		galaxy::api::GalaxyID GetID() const;

		void SetMaxMembers(uint32_t value);
		uint32_t GetMaxMembers() const;
		uint32_t GetMemberCount() const;
		bool IsFull() const;
		galaxy::api::GalaxyID GetMemberByIndex(size_t index) const;

		void SetType(galaxy::api::LobbyType value);
		galaxy::api::LobbyType GetType() const;

		void SetJoinable(bool value);
		bool IsJoinable() const;

		const char* GetData(const char* key) const;
		void SetData(const char* key, const char* value);
		uint32_t GetDataCount() const;
		data_by_index_t GetDataByIndex(size_t index) const;
		void DeleteData(const char* key);

		const char* GetMemberData(galaxy::api::GalaxyID id, const char* key) const;
		bool SetMemberData(galaxy::api::GalaxyID id, const char* key, const char* value);
		uint32_t GetMemberDataCount(galaxy::api::GalaxyID id) const;
		data_by_index_t GetMemberDataByIndex(galaxy::api::GalaxyID id, size_t index) const;
		void DeleteMemberData(galaxy::api::GalaxyID id, const char* key, const char* value);

		galaxy::api::GalaxyID GetOwner() const;

		uint32_t SendMsg(galaxy::api::GalaxyID sender, const std::string data);
		bool AddMsg(const Message& message);
		uint32_t GetMsg(uint32_t messageID, galaxy::api::GalaxyID& senderID, char* msg, uint32_t msgLength);

		data_t GetAllData() const;
		user_data_t GetAllMemberData() const;
		data_t GetAllMemberData(galaxy::api::GalaxyID id) const;

		void SetAllData(const data_t& in_data);
		void SetAllMemberData(const user_data_t& in_data);
		bool SetAllMemberData(galaxy::api::GalaxyID id, const data_t& in_data);
	};
}
