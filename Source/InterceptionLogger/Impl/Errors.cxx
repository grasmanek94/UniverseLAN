#include "Errors.hxx"

#include <Tracer.hxx>
#include <GalaxyDLL.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	Error::Error(InterfaceInstances* intf)
	{
	}

	Error::~Error()
	{
	}

	const char* Error::GetName() const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IERROR | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = RealGalaxyDLL_GetError()->GetName();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("GetName: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	const char* Error::GetMsg() const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IERROR | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = RealGalaxyDLL_GetError()->GetMsg();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("GetMsg: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	IError::Type Error::GetType() const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IERROR | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = RealGalaxyDLL_GetError()->GetType();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("GetType: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
}
