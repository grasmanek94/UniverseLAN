#pragma once

#include <Unet_common.h>
#include <Unet/ResultObject.h>

namespace Unet
{
	enum class LeaveReason
	{
		// User intentially left the lobby (LeaveLobby was called)
		UserLeave,

		// All service entry points have been disconnected
		Disconnected,

		// User was kicked from the lobby
		Kicked,
	};

	struct LobbyLeftResult : public ResultObject
	{
		LeaveReason Reason;
	};
}
