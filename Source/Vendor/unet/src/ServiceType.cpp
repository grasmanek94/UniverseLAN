#include <Unet_common.h>
#include <Unet/ServiceType.h>

Unet::ServiceType Unet::GetServiceTypeByName(const char* str)
{
	if (!strcmp(str, "steam")) {
		return ServiceType::Steam;
	} else if (!strcmp(str, "galaxy")) {
		return ServiceType::Galaxy;
	} else if (!strcmp(str, "enet")) {
		return ServiceType::Enet;
	}
	return ServiceType::None;
}

const char* Unet::GetServiceNameByType(ServiceType type)
{
	switch (type) {
	case ServiceType::Steam: return "steam";
	case ServiceType::Galaxy: return "galaxy";
	case ServiceType::Enet: return "enet";
	default: return "none";
	}
}
