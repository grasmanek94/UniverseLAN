#include <Unet_common.h>
#include <Unet/Results/LobbyListResult.h>
#include <Unet/Context.h>

Unet::LobbyInfo* Unet::LobbyListResult::AddEntryPoint(const xg::Guid &guid, const ServiceID &newEntryPoint)
{
	for (auto &lobbyInfo : Lobbies) {
		if (lobbyInfo.UnetGuid != guid) {
			continue;
		}

		if (lobbyInfo.GetEntryPoint(newEntryPoint.Service) != nullptr) {
			assert(false); // Entry point already exists in the lobby info!
			return nullptr;
		}

		lobbyInfo.EntryPoints.emplace_back(newEntryPoint);
		return &lobbyInfo;
	}

	LobbyInfo newLobbyInfo;
	newLobbyInfo.UnetGuid = guid;
	newLobbyInfo.EntryPoints.emplace_back(newEntryPoint);
	Lobbies.emplace_back(newLobbyInfo);

	return &Lobbies[Lobbies.size() - 1];
}

int Unet::LobbyListResult::GetLobbyNumPlayers(const LobbyInfo &lobbyInfo) const
{
	std::vector<std::pair<ServiceType, int>> items;

	for (auto service : Ctx->m_services) {
		auto entry = lobbyInfo.GetEntryPoint(service->GetType());
		if (entry == nullptr) {
			continue;
		}

		int numPlayers = service->GetLobbyPlayerCount(*entry);
		items.emplace_back(std::make_pair(entry->Service, numPlayers));
	}

	ServiceType highestService = ServiceType::None;
	int highest = -1;

	for (auto &pair : items) {
		if (highest >= 0 && pair.second != highest) {
			Ctx->GetCallbacks()->OnLogWarn(strPrintF("Number of players is different between service %s and %s! (%d and %d)",
				GetServiceNameByType(highestService), GetServiceNameByType(pair.first),
				highest, pair.second
			));
		}

		if (highest == -1 || pair.second > highest) {
			highestService = pair.first;
			highest = pair.second;
		}
	}

	return highest;
}

int Unet::LobbyListResult::GetLobbyMaxPlayers(const LobbyInfo &lobbyInfo) const
{
	std::vector<std::pair<ServiceType, int>> items;

	for (auto service : Ctx->m_services) {
		auto entry = lobbyInfo.GetEntryPoint(service->GetType());
		if (entry == nullptr) {
			continue;
		}

		int maxPlayers = service->GetLobbyMaxPlayers(*entry);
		items.emplace_back(std::make_pair(entry->Service, maxPlayers));
	}

	ServiceType lowestService = ServiceType::None;
	int lowest = 0;

	for (auto &pair : items) {
		if (lowest > 0 && pair.second != lowest) {
			Ctx->GetCallbacks()->OnLogWarn(strPrintF("Max players is different between service %s and %s! (%d and %d)",
				GetServiceNameByType(lowestService), GetServiceNameByType(pair.first),
				lowest, pair.second
			));
		}

		if (lowest == 0 || pair.second < lowest) {
			lowestService = pair.first;
			lowest = pair.second;
		}
	}

	return lowest;
}

std::string Unet::LobbyListResult::GetLobbyData(const LobbyInfo &lobbyInfo, const char* name) const
{
	ServiceType firstService = ServiceType::None;
	std::string ret;

	for (size_t i = 0; i < lobbyInfo.EntryPoints.size(); i++) {
		auto &entry = lobbyInfo.EntryPoints[i];

		auto service = Ctx->GetService(entry.Service);
		if (service == nullptr) {
			continue;
		}

		std::string str = service->GetLobbyData(entry, name);
		if (str == "") {
			continue;
		}

		if (i == 0) {
			firstService = entry.Service;
			ret = str;
		} else if (ret != str) {
			Ctx->GetCallbacks()->OnLogWarn(strPrintF("Data \"%s\" is different between service %s and %s! (\"%s\" and \"%s\")",
				name,
				GetServiceNameByType(firstService), GetServiceNameByType(entry.Service),
				ret.c_str(), str.c_str()
			));
		}
	}

	return ret;
}

std::vector<Unet::LobbyData> Unet::LobbyListResult::GetLobbyData(const LobbyInfo &lobbyInfo) const
{
	std::vector<std::pair<ServiceType, LobbyData>> items;

	for (auto &entry : lobbyInfo.EntryPoints) {
		auto service = Ctx->GetService(entry.Service);
		if (service == nullptr) {
			continue;
		}

		int numData = service->GetLobbyDataCount(entry);
		for (int i = 0; i < numData; i++) {
			auto data = service->GetLobbyData(entry, i);

			auto it = std::find_if(items.begin(), items.end(), [&data](const std::pair<ServiceType, LobbyData> &d) {
				return d.second.Name == data.Name;
			});

			if (it == items.end()) {
				items.emplace_back(std::make_pair(entry.Service, data));
			} else {
				if (it->second.Value != data.Value) {
					Ctx->GetCallbacks()->OnLogWarn(strPrintF("Data \"%s\" is different between service %s and %s! (\"%s\" and \"%s\")",
						data.Name.c_str(),
						GetServiceNameByType(it->first), GetServiceNameByType(entry.Service),
						it->second.Value.c_str(), data.Value.c_str()
					));
				}
			}
		}
	}

	std::vector<LobbyData> ret;
	for (auto &pair : items) {
		ret.emplace_back(pair.second);
	}
	return ret;
}
