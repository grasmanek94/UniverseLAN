#include <Unet_common.h>
#include <Unet/LobbyListFilter.h>

void Unet::LobbyListFilter::AddStringFilter(const char* key, const char* value, StringFilter::Type type)
{
	StringFilter newFilter;
	newFilter.m_key = key;
	newFilter.m_value = value;
	newFilter.m_type = type;
	m_stringFilters.emplace_back(newFilter);
}
