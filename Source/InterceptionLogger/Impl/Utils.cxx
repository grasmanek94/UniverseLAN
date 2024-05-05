#if GALAXY_BUILD_FEATURE_HAS_IUTILS

#include "Utils.hxx"

#include "Listeners/UtilsListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IUTILS;
	}

	UtilsImpl::UtilsImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
		listeners.AddListener<NotificationListener>();
#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
		listeners.AddListener<OverlayVisibilityChangeListener>();
		listeners.AddListener<OverlayInitializationStateChangeListener>();
#endif
#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
		listeners.AddListener<GogServicesConnectionStateListener>();
#endif
	}

	UtilsImpl::~UtilsImpl() {
		listeners.UnregisterAllListeners();
	}

	void UtilsImpl::GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("imageID: {}", imageID));
		}

		intf()->GetImageSize(imageID, width, height);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("width: {}", width));
			trace.write_all(std::format("height: {}", height));
		}
	}

	void UtilsImpl::GetImageRGBA(uint32_t imageID, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("imageID: {}", imageID));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetImageRGBA(imageID, buffer, bufferLength);
	}

	void UtilsImpl::RegisterForNotification(const char* type) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("type: {}", util::safe_fix_null_char_ptr_annotate_ret(type)));
		}

		intf()->RegisterForNotification(type);
	}

	uint32_t UtilsImpl::GetNotification(NotificationID notificationID
#if (GALAXY_VERSION) > 11240
		, bool& consumable
#endif
		, char* type, uint32_t typeLength, void* content, uint32_t contentSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };
		
		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("notificationID: {}", notificationID));
			trace.write_all(std::format("type: {}", (void*)type));
			trace.write_all(std::format("typeLength: {}", typeLength));
			trace.write_all(std::format("content: {}", (void*)content));
			trace.write_all(std::format("contentSize: {}", contentSize));
		}

		auto result = intf()->GetNotification(notificationID
#if (GALAXY_VERSION) > 11240
			, consumable
#endif
			, type, typeLength, content, contentSize
		);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
#if (GALAXY_VERSION) > 11240
			trace.write_all(std::format("consumable: {}", consumable));
#endif
			trace.write_all(std::format("type: {}", util::safe_fix_null_char_ptr_annotate(type, typeLength)));
			trace.write_all(std::format("content: {}", util::safe_fix_null_char_ptr_annotate((const char*)content, contentSize)));
		}

		return result;
	}

	void UtilsImpl::ShowOverlayWithWebPage(const char* url) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("url: {}", util::safe_fix_null_char_ptr_annotate_ret(url)));
		}

		intf()->ShowOverlayWithWebPage(url);
	}

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	bool UtilsImpl::IsOverlayVisible() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->IsOverlayVisible();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	OverlayState UtilsImpl::GetOverlayState() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetOverlayState();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}

#endif
#if GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
	void UtilsImpl::DisableOverlayPopups(const char* popupGroup) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("popupGroup: {}", util::safe_fix_null_char_ptr_annotate_ret(popupGroup)));
		}

		intf()->DisableOverlayPopups(popupGroup);
	}
#endif

#if (GALAXY_VERSION) > 11240
	GogServicesConnectionState UtilsImpl::GetGogServicesConnectionState() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetGogServicesConnectionState();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
#endif
}

#endif
