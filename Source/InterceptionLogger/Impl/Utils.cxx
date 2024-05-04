#if GALAXY_BUILD_FEATURE_HAS_IUTILS

#include "Utils.hxx"

#include <Tracer.hxx>
#include <GalaxyDLL.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;
	UtilsImpl::UtilsImpl(InterfaceInstances* intf) : intf{ intf }
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
	}

	UtilsImpl::~UtilsImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
	}

	void UtilsImpl::GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("imageID: {}", imageID));
		}

		RealGalaxyDLL_Utils()->GetImageSize(imageID, width, height);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("width: {}", width));
			trace.write_all(std::format("height: {}", height));
		}
	}

	void UtilsImpl::GetImageRGBA(uint32_t imageID, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("imageID: {}", imageID));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Utils()->GetImageRGBA(imageID, buffer, bufferLength);
	}

	void UtilsImpl::RegisterForNotification(const char* type) {
		tracer::Trace trace { type, __FUNCTION__ };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("type: {}", util::safe_fix_null_char_ptr_annotate_ret(type)));
		}

		RealGalaxyDLL_Utils()->RegisterForNotification(type);
	}

	uint32_t UtilsImpl::GetNotification(NotificationID notificationID
#if (GALAXY_VERSION) > 11240
		, bool& consumable
#endif
		, char* type, uint32_t typeLength, void* content, uint32_t contentSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };
		
		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("notificationID: {}", notificationID));
			trace.write_all(std::format("type: {}", (void*)type));
			trace.write_all(std::format("typeLength: {}", typeLength));
			trace.write_all(std::format("content: {}", (void*)content));
			trace.write_all(std::format("contentSize: {}", contentSize));
		}

		auto result = RealGalaxyDLL_Utils()->GetNotification(notificationID
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
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("url: {}", util::safe_fix_null_char_ptr_annotate_ret(url)));
		}

		RealGalaxyDLL_Utils()->ShowOverlayWithWebPage(url);
	}

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	bool UtilsImpl::IsOverlayVisible() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		auto result = RealGalaxyDLL_Utils()->IsOverlayVisible();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	OverlayState UtilsImpl::GetOverlayState() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		auto result = RealGalaxyDLL_Utils()->GetOverlayState();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}

#endif
#if GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
	void UtilsImpl::DisableOverlayPopups(const char* popupGroup) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("popupGroup: {}", util::safe_fix_null_char_ptr_annotate_ret(popupGroup)));
		}

		RealGalaxyDLL_Utils()->DisableOverlayPopups(popupGroup);
	}
#endif

#if (GALAXY_VERSION) > 11240
	GogServicesConnectionState UtilsImpl::GetGogServicesConnectionState() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUTILS };

		auto result = RealGalaxyDLL_Utils()->GetGogServicesConnectionState();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
#endif
}

#endif
