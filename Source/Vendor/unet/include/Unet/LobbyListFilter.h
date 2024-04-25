#pragma once

#include <Unet_common.h>
#include <Unet/LobbyInfo.h>

namespace Unet
{
	class LobbyListFilter
	{
		friend class Internal::Context;

	public:
		struct StringFilter
		{
			enum Type
			{
				Matches,
				Contains,
			};

			std::string m_key;
			std::string m_value;
			Type m_type;
		};

	private:
		std::vector<StringFilter> m_stringFilters;

	public:
		void AddStringFilter(const char* key, const char* value, StringFilter::Type type = StringFilter::Matches);
	};
}
