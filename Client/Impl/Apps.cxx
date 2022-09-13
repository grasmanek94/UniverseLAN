#include "Apps.hxx"

#include "UniverseLAN.hxx"

#include <algorithm>
#include <string>

namespace galaxy
{
	namespace api
	{
		AppsImpl::~AppsImpl()
		{
		}

		bool AppsImpl::IsDlcInstalled(ProductID productID) {
			return config->GetEnableAllDLC() || config->IsDLCInstalled(std::to_string(productID));
		}

		const char* AppsImpl::GetCurrentGameLanguage(ProductID productID) {
			return config->GetLanguage().c_str();
		}

		void AppsImpl::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
			std::copy_n(config->GetLanguage().c_str(), std::min((size_t)bufferLength, config->GetLanguage().length()), buffer);
		}
	}
}
