#pragma once

#include "Lobby.hxx"

#include "ContainerGetByIndex.hxx"
#include "GlobalUniqueID.hxx"

#include <GalaxyID.h>
#include <IMatchMaking.h>

#include <map>
#include <ranges>
#include <string>
#include <unordered_map>

namespace universelan {
	using namespace galaxy::api;

	Lobby::Lobby() :
		id{ GlobalUniqueID::get() }, owner_id{}, max_members{}, joinable{}, topology_type{}, type{},
		current_message_id{ 1 }, data{}, user_data{}, messages{} {}

	Lobby::Lobby(GalaxyID owner_id, LobbyType type, uint32_t max_members, bool joinable,
		LobbyTopologyType lobby_topology_type) :
		id{ GlobalUniqueID::get() }, owner_id{ owner_id }, max_members{ max_members }, joinable{ joinable },
		topology_type{ lobby_topology_type }, type{ type }, current_message_id{ 1 }, data{}, user_data{}, messages{} {
		AddMember(owner_id);
	}

	Lobby::Lobby(const Lobby& chat_room) :
		id{ chat_room.id }, owner_id{ chat_room.owner_id }, max_members{ chat_room.max_members },
		joinable{ chat_room.joinable }, topology_type{ chat_room.topology_type }, type{ chat_room.type },
		current_message_id{ chat_room.current_message_id }, data{ chat_room.data }, user_data{ chat_room.user_data },
		messages{ chat_room.messages } {}

	const char* Lobby::GetData(const data_t& data, const char* key) {
		auto entry = data.find(key);
		if (entry == data.end()) {
			return "";
		}

		return entry->second.c_str();
	}

	Lobby::data_by_index_t Lobby::GetDataByIndex(const data_t& data, size_t index) {
		if (data.size() < index) {
			return data_by_index_t{ {},{} };
		}

		auto entry = container_get_by_index(data, index);

		return data_by_index_t{ entry.first, entry.second };
	}

	void Lobby::SetData(data_t& data, const char* key, const char* value) {
		auto entry = data.find(key);
		if (entry == data.end()) {
			data.emplace(key, value);
		}
		else {
			entry->second = value;
		}
	}

	LobbyTopologyType Lobby::GetTopology() const {
		return topology_type;
	}

	void Lobby::SetOwner(GalaxyID new_owner) {
		owner_id = new_owner;
	}

	GalaxyID Lobby::ChooseNewOwner() {
		if (IsMember(owner_id)) {
			return owner_id;
		}

		if (user_data.size() == 0) {
			return 0;
		}

		return user_data.begin()->first;
	}

	const Lobby::view_members_t Lobby::GetMembers() const {
		return std::views::keys(user_data);
	}

	bool Lobby::AddMember(GalaxyID id) {
		return user_data.emplace(id, data_t{}).second;
	}

	bool Lobby::RemoveMember(GalaxyID id) {
		return user_data.erase(id) > 0;
	}

	bool Lobby::IsMember(GalaxyID id) const {
		return user_data.find(id) != user_data.end();
	}

	GalaxyID Lobby::GetID() const {
		return id;
	}

	void Lobby::SetMaxMembers(uint32_t value) {
		max_members = value;
	}

	uint32_t Lobby::GetMaxMembers() const {
		return max_members;
	}

	uint32_t Lobby::GetMemberCount() const {
		return (uint32_t)user_data.size();
	}

	GalaxyID Lobby::GetMemberByIndex(size_t index) const {
		if (user_data.size() < index) {
			return 0;
		}

		return container_get_by_index(user_data, index).first;
	}

	void Lobby::SetType(LobbyType value) {
		type = value;
	}

	void Lobby::SetJoinable(bool value) {
		joinable = value;
	}

	bool Lobby::IsJoinable() const {
		return joinable;
	}

	LobbyType Lobby::GetType() const {
		return type;
	}

	const char* Lobby::GetData(const char* key) const {
		return GetData(data, key);
	}

	void Lobby::SetData(const char* key, const char* value) {
		SetData(data, key, value);
	}

	uint32_t Lobby::GetDataCount() const {
		return (uint32_t)data.size();
	}

	Lobby::data_by_index_t Lobby::GetDataByIndex(size_t index) const {
		return GetDataByIndex(data, index);
	}

	void Lobby::DeleteData(const char* key) {
		SetData(key, "");
	}

	const char* Lobby::GetMemberData(GalaxyID id, const char* key) const {
		auto user = user_data.find(id);
		if (user == user_data.end()) {
			return "";
		}

		return GetData(user->second, key);
	}

	void Lobby::SetMemberData(GalaxyID id, const char* key, const char* value) {
		auto user = user_data.find(id);
		if (user == user_data.end()) {
			return;
		}

		SetData(user->second, key, value);
	}

	uint32_t Lobby::GetMemberDataCount(GalaxyID id) const {
		auto user = user_data.find(id);
		if (user == user_data.end()) {
			return 0;
		}

		return (uint32_t)user->second.size();
	}

	Lobby::data_by_index_t Lobby::GetMemberDataByIndex(GalaxyID id, size_t index) const {
		auto user = user_data.find(id);
		if (user == user_data.end()) {
			return data_by_index_t{ {},{} };
		}

		return GetDataByIndex(user->second, index);
	}

	void Lobby::DeleteMemberData(GalaxyID id, const char* key, const char* value) {
		SetMemberData(id, key, "");
	}

	GalaxyID Lobby::GetOwner() const {
		return owner_id;
	}

	bool Lobby::SendMsg(GalaxyID sender, const std::string data) {
		if (!IsMember(sender)) {
			return false;
		}

		Message message{ current_message_id, sender, data };

		++current_message_id;

		return messages.emplace(message.message_id, message).second;
	}

	uint32_t Lobby::GetMsg(uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
		auto message = messages.find(messageID);
		if (message == messages.end()) {
			return 0;
		}

		Message& entry = message->second;

		uint32_t min_size = std::min(msgLength, (uint32_t)entry.data.size());
		senderID = entry.sender;
		std::copy_n(entry.data.begin(), min_size, msg);

		return min_size;
	}
}
