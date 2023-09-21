#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER

#include "TestCaseClientDetails.hxx"

class OtherSessionStartListenerImplGlobal : public galaxy::api::GlobalOtherSessionStartListener
{
public:
	using on_other_session_started_func_t = std::function<void()>;

private:
	on_other_session_started_func_t on_other_session_started;

public:
	OtherSessionStartListenerImplGlobal(
		on_other_session_started_func_t on_other_session_started = nullptr) :
		on_other_session_started{ on_other_session_started } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OtherSessionStartListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOtherSessionStarted() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_other_session_started != nullptr) {
			on_other_session_started();
		}
	}
};

class OtherSessionStartListenerImplLocal : public galaxy::api::IOtherSessionStartListener
{
public:
	using on_other_session_started_func_t = std::function<void()>;

private:
	on_other_session_started_func_t on_other_session_started;

public:
	OtherSessionStartListenerImplLocal(
		on_other_session_started_func_t on_other_session_started = nullptr) :
		on_other_session_started{ on_other_session_started } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OtherSessionStartListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOtherSessionStarted() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_other_session_started != nullptr) {
			on_other_session_started();
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerOtherSessionStartListenerImplGlobal : public galaxy::api::GameServerGlobalOtherSessionStartListener
{
public:
	using on_other_session_started_func_t = std::function<void()>;

private:
	on_other_session_started_func_t on_other_session_started;

public:
	GameServerOtherSessionStartListenerImplGlobal(
		on_other_session_started_func_t on_other_session_started = nullptr) :
		on_other_session_started{ on_other_session_started } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerOtherSessionStartListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOtherSessionStarted() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_other_session_started != nullptr) {
			on_other_session_started();
		}
	}
};

#endif
#endif
