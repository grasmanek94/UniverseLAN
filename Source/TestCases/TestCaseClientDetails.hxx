#pragma once

#include <array>
#include <string_view>

namespace galaxy::api {
	using namespace std::string_view_literals;

	constexpr std::string_view PRODUCT_ID_STR = "1767680123";
	constexpr unsigned long long PRODUCT_ID_INT = 1767680123ULL;

	constexpr std::string_view CLIENT_ID_STR = "50225266424144145";
	constexpr unsigned long long CLIENT_ID_INT = 50225266424144145ULL;

	constexpr std::string_view CLIENT_SECRET = "45955f1104f99b625a5733fa1848479b43d63bdb98f0929e37c9affaf900e99f";

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


#ifndef GALAXY_SDK_USER_CREDENTIALS
	constexpr std::array USER_CREDENTIALS = {
		std::array{""sv,""sv}
	};

#else
	constexpr std::array USER_CREDENTIALS = {
		std::array{GALAXY_SDK_USER_CREDENTIALS_USER1_NAME sv,GALAXY_SDK_USER_CREDENTIALS_USER1_PASSWORD sv},
		std::array{GALAXY_SDK_USER_CREDENTIALS_USER2_NAME sv,GALAXY_SDK_USER_CREDENTIALS_USER2_PASSWORD sv}
	};
#endif


}
