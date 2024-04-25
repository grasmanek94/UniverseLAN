#pragma once

#include <Unet_common.h>
#include <Unet/ResultObject.h>
#include <Unet/Lobby.h>

namespace Unet
{
	struct LobbyJoinResult : public ResultObject
	{
		xg::Guid JoinGuid;
		Lobby* JoinedLobby;
	};
}
