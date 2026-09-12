#include <MiniDump.hxx>
#include <ReturnAddress.hxx>
#include <Stacker.hxx>
#include <Tracer.hxx>

#include <gtest/gtest.h>

#include <type_traits>

namespace {

class RecordingUnhandledExceptionCallback final : public universelan::tracer::IUnhandledExceptionCallback {
public:
    void UnhandledExceptionOccurred(bool unknown_exception, const std::string exception_type, const std::string& exception_message, bool error_occured_during_stack_walk, const universelan::tracer::CallStackEntries& call_stack) override
    {
        unknown_exception_ = unknown_exception;
        exception_type_ = exception_type;
        exception_message_ = exception_message;
        error_occured_during_stack_walk_ = error_occured_during_stack_walk;
        call_stack_ = call_stack;
    }

    bool unknown_exception_ = false;
    std::string exception_type_;
    std::string exception_message_;
    bool error_occured_during_stack_walk_ = false;
    universelan::tracer::CallStackEntries call_stack_;
};

TEST(TracerValues, DefinesDistinctSingleBitTraceFlags)
{
    EXPECT_EQ(universelan::tracer::bit(0), 1ULL);
    EXPECT_EQ(universelan::tracer::bit(28), 1ULL << 28);
    EXPECT_EQ(universelan::tracer::Trace::INFORMATIONAL, 0U);
    EXPECT_NE(universelan::tracer::Trace::ARGUMENTS, universelan::tracer::Trace::RETURN_VALUES);
    EXPECT_NE(universelan::tracer::Trace::TRACE_ALL_FLAGS, universelan::tracer::Trace::NETWORK_P2P_CONTENTS);
}

TEST(TracerValues, PreservesCallStackAndExceptionCallbackValues)
{
    universelan::tracer::CallStackEntry entry{};
    entry.offset = 42;
    entry.module_name = "module";
    entry.function = "function";
    entry.file.path = "source.cxx";
    entry.file.line_number = 7;
    universelan::tracer::CallStackEntries stack{ entry };
    RecordingUnhandledExceptionCallback callback;

    callback.UnhandledExceptionOccurred(true, "type", "message", true, stack);

    EXPECT_TRUE(callback.unknown_exception_);
    EXPECT_EQ(callback.exception_type_, "type");
    EXPECT_EQ(callback.exception_message_, "message");
    EXPECT_TRUE(callback.error_occured_during_stack_walk_);
    ASSERT_EQ(callback.call_stack_.size(), 1U);
    EXPECT_EQ(callback.call_stack_.front().offset, 42U);
    EXPECT_EQ(callback.call_stack_.front().module_name, "module");
    EXPECT_EQ(callback.call_stack_.front().function, "function");
    EXPECT_EQ(callback.call_stack_.front().file.path, "source.cxx");
    EXPECT_EQ(callback.call_stack_.front().file.line_number, 7U);
}

TEST(TracerValues, ExposesPlatformIndependentApiDeclarations)
{
    const void* return_address = _ReturnAddress();
    static_assert(std::is_same_v<decltype(&universelan::tracer::CreateMiniDump), void (*)(const char*, int)>);
    static_assert(std::is_destructible_v<universelan::tracer::Trace>);

    SUCCEED() << return_address;
}

} // namespace
