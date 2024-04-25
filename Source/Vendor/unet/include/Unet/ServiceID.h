#pragma once

#include <Unet_common.h>
#include <Unet/ServiceType.h>

namespace Unet
{
	class ServiceID
	{
	public:
		ServiceType Service;
		uint64_t ID;

	public:
		ServiceID()
		{
			Service = ServiceType::None;
			ID = 0;
		}

		ServiceID(ServiceType type, uint64_t id)
		{
			Service = type;
			ID = id;
		}

		bool IsValid() const
		{
			return Service != ServiceType::None;
		}

		bool operator==(const ServiceID &other) const
		{
			return Service == other.Service && ID == other.ID;
		}

		bool operator==(uint64_t id) const
		{
			return ID == id;
		}

		bool operator!=(const ServiceID &other) const
		{
			return !operator==(other);
		}

		bool operator!=(uint64_t id) const
		{
			return !operator==(id);
		}
	};
}
