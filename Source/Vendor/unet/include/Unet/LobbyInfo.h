#pragma once

#include <Unet_common.h>
#include <Unet/ServiceID.h>

namespace Unet
{
	enum class LobbyPrivacy
	{
		Public,
		Private,
	};

	struct LobbyInfo
	{
		bool IsHosting = false;
		LobbyPrivacy Privacy = LobbyPrivacy::Public;

		int NumPlayers = 0;
		int MaxPlayers = 0;

		xg::Guid UnetGuid;

		std::string Name;
		std::vector<ServiceID> EntryPoints;

		const ServiceID* GetEntryPoint(ServiceType service) const;
	};
}
