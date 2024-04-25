#pragma once

#include <Unet_common.h>
#include <Unet/ResultObject.h>
#include <Unet/LobbyInfo.h>
#include <Unet/LobbyData.h>
#include <Unet/LobbyListFilter.h>

namespace Unet
{
	struct LobbyListResult : public ResultObject
	{
		friend class Internal::Context;

	private:
		Internal::Context* Ctx;
		LobbyListFilter Filter;

	public:
		// The lobbies that were found
		std::vector<LobbyInfo> Lobbies;

		// How many lobbies were filtered out by the LobbyListFilter
		int NumFiltered = 0;

		// Adds an entry point to an existing lobby by Guid, or if the lobby doesn't exist, adds a new lobby to the list.
		LobbyInfo* AddEntryPoint(const xg::Guid &guid, const ServiceID &newEntryPoint);

		// Get the number of players currently in the lobby as reported by services.
		int GetLobbyNumPlayers(const LobbyInfo &lobbyInfo) const;
		// Get maximum number of players as reported by services.
		int GetLobbyMaxPlayers(const LobbyInfo &lobbyInfo) const;
		// Get lobby data as reported by services.
		std::string GetLobbyData(const LobbyInfo &lobbyInfo, const char* name) const;
		// Get all lobby data as reported by services.
		std::vector<LobbyData> GetLobbyData(const LobbyInfo &lobbyInfo) const;
	};
}
