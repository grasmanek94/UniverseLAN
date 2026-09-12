#if GALAXY_BUILD_FEATURE_HAS_IAPPS

#include "Apps.hxx"

#include "Listeners/AppsListener.hxx"

#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IAPPS;
	}

	AppsImpl::AppsImpl(FuncT::F intf, IListenerRegistrar* notifications, bool force_dlc_check) :
		intf{ intf },
		notifications{ notifications },
		force_dlc_check{ force_dlc_check },
		listeners{ notifications }
	{
#if GALAXY_BUILD_FEATURE_HAS_IAPPS_ISDLCOWNED
		listeners.AddListener<IsDlcOwnedListener>();
#endif
	}

	AppsImpl::~AppsImpl() {}

	bool AppsImpl::IsDlcInstalled(ProductID productID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS /* Some games call this frequently */ };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all("productID: {}", productID);
		}

		auto result = force_dlc_check || intf()->IsDlcInstalled(productID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all("result: {}", result);
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE
	const char* AppsImpl::GetCurrentGameLanguage(ProductID productID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all("productID: {}", productID);
		}

		auto language = intf()->GetCurrentGameLanguage(productID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all("language: {}", language);
		}

		return language;
	}

	void AppsImpl::GetCurrentGameLanguageCopy(char* buffer, uint32_t bufferLength, ProductID productID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all("buffer: {}", (void*)buffer);
			trace.write_all("bufferLength: {}", bufferLength);
			trace.write_all("productID: {}", productID);
		}

		intf()->GetCurrentGameLanguageCopy(buffer, bufferLength, productID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all("language: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength));
		}
	}
#endif


#if GALAXY_BUILD_FEATURE_HAS_IAPPS_LANGUAGECODE
	const char* AppsImpl::GetCurrentGameLanguageCode(ProductID productID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all("productID: {}", productID);
		}

		auto lang_code = intf()->GetCurrentGameLanguageCode(productID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all("lang_code: {}", lang_code);
		}

		return lang_code;
	}

	void AppsImpl::GetCurrentGameLanguageCodeCopy(char* buffer, uint32_t bufferLength, ProductID productID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all("buffer: {}", (void*)buffer);
			trace.write_all("bufferLength: {}", bufferLength);
			trace.write_all("productID: {}", productID);
		}

		intf()->GetCurrentGameLanguageCodeCopy(buffer, bufferLength, productID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all("lang_code: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_ISDLCOWNED
	void AppsImpl::IsDlcOwned(ProductID productID, IIsDlcOwnedListener* const listener)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IAPPS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all("productID: {}", productID);
			trace.write_all("listener: {}", (void*)listener);
		}

		if (force_dlc_check) {
			listener->OnDlcCheckSuccess(productID, true);
		}
		else {
			intf()->IsDlcOwned(productID, IsDlcOwnedListener::encapsulate(listener));
		}
	}
#endif
}

#endif
