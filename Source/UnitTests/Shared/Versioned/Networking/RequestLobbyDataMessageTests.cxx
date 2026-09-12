#include <Networking/Messages/RequestLobbyDataMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestLobbyDataMessage, SerializesRequestAndLobbyWithoutResponse)
{
	galaxy::api::GalaxyID lobby(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestLobbyDataMessage(7, lobby));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64());
	EXPECT_EQ(restored.data, nullptr);
	EXPECT_EQ(restored.fail_reason, galaxy::api::ILobbyDataRetrieveListener::FAILURE_REASON_UNDEFINED);
}
