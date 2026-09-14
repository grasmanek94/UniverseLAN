#include "Host.hxx"

#include <array>
#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_IAPPS && GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE
namespace
{
constexpr galaxy::api::ProductID installedDlc = 210001;
constexpr galaxy::api::ProductID disabledDlc = 210002;
constexpr galaxy::api::ProductID absentDlc = 210003;

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_ISDLCOWNED
struct DlcOwnedListener final : galaxy::api::IIsDlcOwnedListener
{
    unsigned int successes = 0;
    unsigned int failures = 0;
    galaxy::api::ProductID productId = 0;
    bool owned = false;

    void OnDlcCheckSuccess(const galaxy::api::ProductID value, const bool valueOwned) override
    {
        ++successes;
        productId = value;
        owned = valueOwned;
    }

    void OnDlcCheckFailure(const galaxy::api::ProductID, FailureReason) override { ++failures; }
};
#endif
}

bool appsConfigAndDlcOwnership(Api& api, const Arguments& arguments)
{
    galaxy::api::IApps* apps = api.apps();
    if (apps == nullptr || !apps->IsDlcInstalled(installedDlc) || apps->IsDlcInstalled(disabledDlc) || apps->IsDlcInstalled(absentDlc)) return false;

    const char* language = apps->GetCurrentGameLanguage();
    std::array<char, 7> languageCopy{};
    std::array<char, 4> languageTruncated{};
    apps->GetCurrentGameLanguageCopy(languageCopy.data(), static_cast<std::uint32_t>(languageCopy.size()));
    apps->GetCurrentGameLanguageCopy(languageTruncated.data(), static_cast<std::uint32_t>(languageTruncated.size()));
    if (language == nullptr || std::string(language) != "polish" || std::string(languageCopy.data(), 6) != "polish" || languageCopy.back() != '\0'
        || std::string(languageTruncated.data(), 3) != "pol" || languageTruncated.back() != '\0') return false;

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_LANGUAGECODE
    const char* languageCode = apps->GetCurrentGameLanguageCode();
    std::array<char, 6> languageCodeCopy{};
    std::array<char, 3> languageCodeTruncated{};
    apps->GetCurrentGameLanguageCodeCopy(languageCodeCopy.data(), static_cast<std::uint32_t>(languageCodeCopy.size()));
    apps->GetCurrentGameLanguageCodeCopy(languageCodeTruncated.data(), static_cast<std::uint32_t>(languageCodeTruncated.size()));
    if (languageCode == nullptr || std::string(languageCode) != "pl-PL" || std::string(languageCodeCopy.data(), 5) != "pl-PL" || languageCodeCopy.back() != '\0'
        || std::string(languageCodeTruncated.data(), 2) != "pl" || languageCodeTruncated.back() != '\0') return false;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_ISDLCOWNED
    DlcOwnedListener specificListener;
    DlcOwnedListener globalListener;
    galaxy::api::IListenerRegistrar* registrar = galaxy::api::ListenerRegistrar();
    if (registrar == nullptr) return false;
    registrar->Register(galaxy::api::IIsDlcOwnedListener::GetListenerType(), &globalListener);
    apps->IsDlcOwned(installedDlc, &specificListener);
    const bool completed = pumpUntil(api, arguments.timeoutSeconds, [&specificListener, &globalListener]
    {
        return specificListener.successes != 0 || specificListener.failures != 0 || globalListener.successes != 0 || globalListener.failures != 0;
    });
    registrar->Unregister(galaxy::api::IIsDlcOwnedListener::GetListenerType(), &globalListener);
    if (!completed || specificListener.successes != 1 || specificListener.failures != 0 || specificListener.productId != installedDlc || !specificListener.owned
        || globalListener.successes != 1 || globalListener.failures != 0 || globalListener.productId != installedDlc || !globalListener.owned) return false;
#endif

    return true;
}
#endif
}
