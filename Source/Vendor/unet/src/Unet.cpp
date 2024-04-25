#include <Unet_common.h>
#include <Unet.h>
#include <Unet/Context.h>

Unet::IContext* Unet::CreateContext(int numChannels)
{
	return new Internal::Context(numChannels);
}

void Unet::DestroyContext(IContext* ctx)
{
	delete ctx;
}

const char* Unet::GetVersion()
{
	return "0.00.1";
}
