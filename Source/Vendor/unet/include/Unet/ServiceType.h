#pragma once

namespace Unet
{
	enum class ServiceType
	{
		None,

		Steam,
		Galaxy,
		Enet,
	};

	ServiceType GetServiceTypeByName(const char* str);
	const char* GetServiceNameByType(ServiceType type);
}
