#include <Unet_common.h>
#include <Unet/LobbyInfo.h>

const Unet::ServiceID* Unet::LobbyInfo::GetEntryPoint(Unet::ServiceType service) const
{
	for (auto &entryPoint : EntryPoints) {
		if (entryPoint.Service == service) {
			return &entryPoint;
		}
	}
	return nullptr;
}
