#pragma once

#include <array>
#include <format>
#include <string_view>
#include <magic_enum/magic_enum.hpp>

namespace galaxy::api {
	using namespace std::string_view_literals;

#ifndef GALAXY_SDK_CLIENT_ID
	constexpr std::string_view CLIENT_ID = "50225266424144145";
	constexpr std::string_view CLIENT_SECRET = "45955f1104f99b625a5733fa1848479b43d63bdb98f0929e37c9affaf900e99f";
#else
	constexpr std::string_view CLIENT_ID = GALAXY_SDK_CLIENT_ID;
	constexpr std::string_view CLIENT_SECRET = GALAXY_SDK_CLIENT_SECRET;
#endif

	// List of all in-game achievements api keys
	constexpr std::array ACHIEVEMENTS_LIST = {
		"launchTheGame"sv,
		"putBlack"sv,
		"putBlue"sv,
		"putBrown"sv,
		"putGreen"sv,
		"putPink"sv,
		"putRed"sv,
		"putYellow"sv,
		"winSPRound"sv,
		"win2PRound"sv,
		"draw2PRound"sv,
		"winMPRound"sv,
		"drawMPRound"sv,
		"loseMPRound"sv
	};

	//  all in-game statistics api keys
	constexpr std::array STATISTICS_FLOAT_LIST = {
		"lastScore"sv,
		"highestScore"sv
	};

	//  all in-game statistics api keys
	constexpr std::array STATISTICS_INT_LIST = {
		"fouls"sv,
		"shotsTaken"sv
	};

	//  all in-game leaderboards api keys
	constexpr std::array LEADERBOARDS_LIST = {
		"fouls"sv,
		"highestScore"sv,
		"shotsTaken"sv
	};


#ifndef GALAXY_SDK_USER_CREDENTIALS_USER1_NAME
	constexpr std::array USER_CREDENTIALS = {
		std::array{""sv,""sv}
	};

#else
	constexpr std::array USER_CREDENTIALS = {
		std::array{GALAXY_SDK_USER_CREDENTIALS_USER1_NAME,GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD},
		std::array{GALAXY_SDK_USER_CREDENTIALS_USER2_NAME,GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD}
	};
#endif


}

#include <GalaxyApi.h>

template <>
struct std::formatter<galaxy::api::GalaxyID> : std::formatter<std::string> {
	auto format(galaxy::api::GalaxyID p, format_context& ctx) const {
		return formatter<string>::format(
			std::format("{}({})", p.GetRealID(), magic_enum::enum_name(p.GetIDType())), ctx);
	}
};
