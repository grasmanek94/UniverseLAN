#include "Apps.hxx"

#include <algorithm>

namespace galaxy
{
	namespace api
	{
		AppsImpl::~AppsImpl()
		{
		}

		bool AppsImpl::IsDlcInstalled(ProductID productID) {
			return true;
		}

		const char* AppsImpl::GetCurrentGameLanguage(ProductID productID) {
			return "english";
		}

		void AppsImpl::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
			std::copy_n("english", std::min((size_t)bufferLength, strlen("english")), buffer);
		}
	}
}
