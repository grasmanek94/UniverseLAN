#include "Errors.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IERROR;
	}

	Error::Error(FuncT::F intf) : intf{ intf } {}
	Error::~Error(){}

	const char* Error::GetName() const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetName();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("GetName: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	const char* Error::GetMsg() const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetMsg();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("GetMsg: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	IError::Type Error::GetType() const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetType();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("GetType: {}", magic_enum::enum_name(result)));
		}

		return result;
	}

	bool Error::HasError() const
	{
		return intf() != nullptr;
	}
}
