#include <Impl/ListenerRegistrar.hxx>

#include <gtest/gtest.h>

namespace {

class TestListener : public galaxy::api::GalaxyTypeAwareListener<galaxy::api::USER_DATA>
{};

TEST(ListenerRegistrar, RequestHelperPopsEachRegisteredListenerOnce)
{
	universelan::client::ListenerRegistrarImpl::InternalRequestHelper helper;
	TestListener listener;
	TestListener* restored = nullptr;

	EXPECT_TRUE(helper.emplace(7, &listener));
	EXPECT_FALSE(helper.emplace(7, &listener));
	EXPECT_TRUE(helper.pop(7, restored));
	EXPECT_EQ(restored, &listener);
	EXPECT_FALSE(helper.pop(7, restored));
	EXPECT_EQ(restored, nullptr);
}

TEST(ListenerRegistrar, RequestHelperPreservesExtraStateAndUnregisters)
{
	universelan::client::ListenerRegistrarImpl::InternalRequestHelper helper;
	TestListener listener;
	TestListener* restored = nullptr;
	auto extra = std::make_shared<int>(42);
	std::shared_ptr<int> restored_extra;

	EXPECT_TRUE(helper.emplace(7, &listener, extra));
	EXPECT_TRUE(helper.pop(7, restored, restored_extra));
	EXPECT_EQ(restored, &listener);
	ASSERT_NE(restored_extra, nullptr);
	EXPECT_EQ(*restored_extra, 42);

	EXPECT_TRUE(helper.emplace(8, &listener));
	EXPECT_TRUE(helper.unregister(&listener));
	EXPECT_FALSE(helper.pop(8, restored));
	EXPECT_EQ(restored, nullptr);
	EXPECT_FALSE(helper.unregister(&listener));
}

} // namespace
