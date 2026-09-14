#include "Host.hxx"

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_IUTILS && GALAXY_BUILD_FEATURE_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE && GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM && GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
namespace
{
constexpr const char overlayPageUrl[] = "https://www.gog.com/";
constexpr const char* overlayPopupGroups[] = {"chat_message", "friend_invitation", "game_invitation"};

struct OverlayVisibilityListener final : galaxy::api::GlobalOverlayVisibilityChangeListener
{
    unsigned int callbacks = 0;

    void OnOverlayVisibilityChanged(bool) override { ++callbacks; }
};

struct OverlayInitializationStateListener final : galaxy::api::GlobalOverlayInitializationStateChangeListener
{
    unsigned int callbacks = 0;

    void OnOverlayStateChanged(galaxy::api::OverlayState) override { ++callbacks; }
};
}

bool utilsOverlayDisabledInvariant(Api& api, const Arguments&)
{
    galaxy::api::IUtils* utils = api.utils();
    if (utils == nullptr || utils->GetOverlayState() != galaxy::api::OVERLAY_STATE_DISABLED || utils->IsOverlayVisible()) return false;

    OverlayVisibilityListener visibilityListener;
    OverlayInitializationStateListener stateListener;
    utils->ShowOverlayWithWebPage(overlayPageUrl);
    for (const char* popupGroup : overlayPopupGroups) utils->DisableOverlayPopups(popupGroup);

    for (unsigned int iteration = 0; iteration < 25; ++iteration)
    {
        api.processData();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return utils->GetOverlayState() == galaxy::api::OVERLAY_STATE_DISABLED && !utils->IsOverlayVisible()
        && stateListener.callbacks == 0 && visibilityListener.callbacks == 0;
}
#endif
}
