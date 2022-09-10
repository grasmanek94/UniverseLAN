#include "Apps.hxx"

#include <algorithm>

namespace galaxy
{
	namespace api
	{
		Apps::~Apps()
		{
		}

		bool Apps::IsDlcInstalled(ProductID productID) {
			return true;
		}

		const char* Apps::GetCurrentGameLanguage(ProductID productID) {
			return "english";
		}

		void Apps::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
			std::copy_n("english", std::min((size_t)bufferLength, strlen("english")), buffer);
		}
	}
}
