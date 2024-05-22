#pragma once

#include "TestCaseClientDetails.hxx"

class TestInitListenerGlobal :
	public galaxy::api::GlobalAuthListener
#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	, public galaxy::api::GlobalAccessTokenListener
#endif
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
	, public galaxy::api::GlobalSpecificUserDataListener
#endif
	, public galaxy::api::GlobalUserDataListener
#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	, public galaxy::api::GlobalGogServicesConnectionStateListener
#endif
	, public galaxy::api::GlobalOperationalStateChangeListener
	, public galaxy::api::GlobalPersonaDataChangedListener
{
public:
	using on_test_ready_callback = std::function<void(void)>;

private:
	bool has_access_token_refreshed;
	bool has_signed_in;
	bool has_connected;
	bool has_operational_state_change;
	bool has_person_data_changed;
	bool user_data_received;
	bool performed_init;

	on_test_ready_callback callback;

	void TryInit() {
		if (!has_signed_in ||
			!has_connected ||
			!has_operational_state_change ||
			!has_person_data_changed ||
#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
			!has_access_token_refreshed ||
#endif
			!user_data_received ||
			performed_init)
		{
			return;
		}

		performed_init = true;
		if (callback) {
			callback();
		}
	}

public:

	TestInitListenerGlobal(on_test_ready_callback callback = nullptr,
		bool require_access_token_refresh = true,
		bool require_sign_in = true,
		bool require_connected = true,
		bool require_operational_state_change = true,
		bool require_person_data_changed = true,
		bool require_user_data_received = false) :
		has_access_token_refreshed{ !require_access_token_refresh || !GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER },
		has_signed_in{ !require_sign_in },
		has_connected{ !require_connected || !GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER },
		has_operational_state_change{ !require_operational_state_change },
		has_person_data_changed{ !require_person_data_changed },
		user_data_received{ !require_user_data_received },
		performed_init{ false },
		callback{ callback }
	{
		tracer::Trace trace{ "", __FUNCTION__ };

		TryInit();
	}

	virtual ~TestInitListenerGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAccessTokenChanged() {
		tracer::Trace trace{ "", __FUNCTION__ };

		has_access_token_refreshed = true;
		TryInit();
	}

	virtual void OnSpecificUserDataUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (userID != GET_GALAXY_API(User())->GetGalaxyID() && userID != 0) {
			return;
		}

		user_data_received = true;
		TryInit();
	}

	virtual void OnUserDataUpdated() {
		tracer::Trace trace{ "", __FUNCTION__ };

		user_data_received = true;
		TryInit();
	}

	virtual void OnAuthSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };

		has_signed_in = true;
		TryInit();
	}

	virtual void OnAuthFailure(IAuthListener::FailureReason reason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		has_signed_in = false;
	}

	virtual void OnAuthLost() {
		tracer::Trace trace{ "", __FUNCTION__ };

		has_signed_in = false;
	}

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	virtual void OnConnectionStateChange(GogServicesConnectionState connectionState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (connectionState != GOG_SERVICES_CONNECTION_STATE_CONNECTED) {
			has_connected = false;
			return;
		}

		has_connected = true;
		TryInit();
}
#endif

	virtual void OnOperationalStateChanged(uint32_t operationalState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (!(operationalState & IOperationalStateChangeListener::OperationalState::OPERATIONAL_STATE_SIGNED_IN &&
			operationalState & IOperationalStateChangeListener::OperationalState::OPERATIONAL_STATE_LOGGED_ON)) {
			has_operational_state_change = false;
			return;
		}

		has_operational_state_change = true;
		TryInit();
	}

	virtual void OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (personaStateChange != 0 || (userID != GET_GALAXY_API(User())->GetGalaxyID() && userID != 0)) {
			return;
		}

		has_person_data_changed = true;
		TryInit();
	}
};

#ifdef USE_TESTING_MAIN
std::unique_ptr<tracer::Trace> trace{ nullptr };
DelayRunner delay_runner{};

void perform_test();
void register_listeners();
bool should_keep_running();

int main()
{
	tracer::Trace::InitTracing("TestLog", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(false);
	tracer::Trace::SetTracingEnabled(false);

	GALAXY_INIT();

	register_listeners();

	trace = std::make_unique<tracer::Trace>("", "main");

	GET_GALAXY_API(User())->SignInGalaxy();

	TestInitListenerGlobal test_start_listener{ [&](void) -> void {
		tracer::Trace::SetTracingEnabled(true);
		trace = std::make_unique<tracer::Trace>("::INIT", "main");

		perform_test();
	} };

	while (should_keep_running())
	{
		GET_GALAXY_API_AS_IS(ProcessData());

		delay_runner.Run();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	GALAXY_DEINIT();

	return 0;
}

#endif
