#if GALAXY_BUILD_FEATURE_HAS_IAPPS

#include "Apps.hxx"

#include "UniverseLAN.hxx"

#include <IniData.hxx>
#include <SafeStringCopy.hxx>

#include <algorithm>
#include <format>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;
	AppsImpl::AppsImpl(InterfaceInstances* intf) : intf{ intf } {}

	AppsImpl::~AppsImpl() {}

	bool AppsImpl::IsDlcInstalled(ProductID productID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::HIGH_FREQUENCY_CALLS /* Some games call this frequently */};

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format(
				"productID: {}",
				productID));
		}

		return intf->config->GetEnableAllDLC() || intf->config->IsDLCInstalled(productID);
	}

	const char* AppsImpl::GetCurrentGameLanguage(ProductID productID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format(
				"productID: {}",
				productID));
		}

		return intf->config->GetLanguage().c_str();
	}

	void AppsImpl::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format(
				"productID: {}",
				productID));
		}

		universelan::util::safe_copy_str_n(intf->config->GetLanguage(), buffer, bufferLength);
	}
}

#endif
