#include <Unet_common.h>
#include <Unet/Service.h>

Unet::Service::Service(Internal::Context* ctx, int numChannels)
{
	m_ctx = ctx;
	m_numChannels = numChannels;
}
