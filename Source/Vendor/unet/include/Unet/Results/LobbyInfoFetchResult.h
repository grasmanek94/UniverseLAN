#pragma once

#include <Unet_common.h>
#include <Unet/ResultObject.h>
#include <Unet/LobbyInfo.h>

namespace Unet
{
	struct LobbyInfoFetchResult : public ResultObject
	{
		ServiceID ID;
		LobbyInfo Info;
	};
}
