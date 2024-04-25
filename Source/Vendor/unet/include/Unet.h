#pragma once

#include <Unet_common.h>

#include <Unet/ICallbacks.h>
#include <Unet/IContext.h>

namespace Unet
{
	// Create a context
	IContext* CreateContext(int numChannels = 1);

	// Destroy a context
	void DestroyContext(IContext* ctx);

	// Get the current version string of the library
	const char* GetVersion();
}
