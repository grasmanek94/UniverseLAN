#include <TestCaseClientDetails.hxx>

int main()
{
	tracer::Trace::InitTracing(".", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(true);

	tracer::Trace trace{ "", __FUNCTION__ };

	GALAXY_INIT();

	trace.write_all("galaxy::api::Init performed");

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	AccessTokenListenerImplGlobal accesstokenlistener{};
#endif

	AchievementChangeListenerImplGlobal achievementchangelistener{};
	AuthListenerImplGlobal authlistener{};

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
	OtherSessionStartListenerImplGlobal othersessionstartlistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
	SpecificUserDataListenerImplGlobal specificuserdatalistener{};
#endif
	StatsAndAchievementsStoreListenerImplGlobal statsandachievementsstorelistener{};

	UserDataListenerImplGlobal userdatalistener{};

	trace.write_all("Listeners registered");

	auto credentials = USER_CREDENTIALS[0];

	trace.write_all("SignInCredentials..");

	GET_GALAXY_API(User())->SignInCredentials(credentials[0].data(), credentials[1].data());

	trace.write_all(".OK");

	while (true)
	{
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
		galaxy_api->ProcessData();
#else
		galaxy::api::ProcessData();
#endif

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	GALAXY_DEINIT();

	return 0;
}
