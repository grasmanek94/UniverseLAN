#if GALAXY_BUILD_FEATURE_HAS_IAPPS 

#include "AppsListener.hxx"
#include "ProxifySingleShotListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IAPPS;
	}

#if GALAXY_BUILD_FEATURE_HAS_IAPPS_ISDLCOWNED
	void IsDlcOwnedListener::OnDlcCheckSuccess(ProductID producId, bool isOwned) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", producId));
			trace.write_all(std::format("chatRoomID: {}", isOwned));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnDlcCheckSuccess(producId, isOwned));
	}

	void IsDlcOwnedListener::OnDlcCheckFailure(ProductID producId, IIsDlcOwnedListener::FailureReason failueReason) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", producId));
			trace.write_all(std::format("failueReason: {}", magic_enum::enum_name(failueReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnDlcCheckFailure(producId, failueReason));
	}
#endif
}
#endif
