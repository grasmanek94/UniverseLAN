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
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IAPPS | tracer::Trace::HIGH_FREQUENCY_CALLS /* Some games call this frequently */};

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("productID: {}", productID));
		}

		bool result = intf->config->GetEnableAllDLC() || intf->config->IsDLCInstalled(productID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE
	const char* AppsImpl::GetCurrentGameLanguage(ProductID productID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IAPPS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("productID: {}", productID));
		}

		const char* language = intf->config->GetLanguage().c_str();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("language: {}", language));
		}

		return language;
	}

	void AppsImpl::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IAPPS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("productID: {}", productID));
		}

		std::string language = intf->config->GetLanguage();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("language: {}", language));
		}

		universelan::util::safe_copy_str_n(language, buffer, bufferLength);
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_LANGUAGECODE
	const char* AppsImpl::GetCurrentGameLanguageCode(ProductID productID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IAPPS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("productID: {}", productID));
		}

		const char* lang_code = intf->config->GetLanguageCode().c_str();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("lang_code: {}", lang_code));
		}

		return lang_code;
	}

	void AppsImpl::GetCurrentGameLanguageCodeCopy(char* buffer, uint32_t bufferLength, ProductID productID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IAPPS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("productID: {}", productID));
		}

		std::string lang_code = intf->config->GetLanguageCode();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("lang_code: {}", lang_code));
		}

		universelan::util::safe_copy_str_n(lang_code, buffer, bufferLength);
	}
#endif

}

#endif
