#include "Apps.hxx"

#include "UniverseLAN.hxx"

#include <IniData.hxx>

#include <algorithm>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;
	AppsImpl::AppsImpl(InterfaceInstances* intf) : intf{ intf } {}

	AppsImpl::~AppsImpl() {}

	bool AppsImpl::IsDlcInstalled(ProductID productID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetEnableAllDLC() || intf->config->IsDLCInstalled(std::to_string(productID));
	}

	const char* AppsImpl::GetCurrentGameLanguage(ProductID productID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetLanguage().c_str();
	}

	void AppsImpl::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
		tracer::Trace trace{ __FUNCTION__ };

		std::copy_n(intf->config->GetLanguage().c_str(), std::min((size_t)bufferLength, intf->config->GetLanguage().length()), buffer);
	}
}