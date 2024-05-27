#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IAPPS 

#include "ProxifySingleShotListener.hxx"

#include <IApps.h>

namespace universelan::client {
	using namespace galaxy::api;

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_ISDLCOWNED
    class IsDlcOwnedListener : public IIsDlcOwnedListener
    {
        IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(IsDlcOwnedListener, IIsDlcOwnedListener);

    public:
        virtual void OnDlcCheckSuccess(ProductID producId, bool isOwned);
        virtual void OnDlcCheckFailure(ProductID producId, FailureReason failueReason);
    };
#endif
}

#endif
