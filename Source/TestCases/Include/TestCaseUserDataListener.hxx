#pragma once

#include "TestCaseClientDetails.hxx"

class UserDataListenerImplGlobal : public galaxy::api::GlobalUserDataListener
{
public:
	using on_user_data_updated_func_t = std::function<void()>;

private:
	on_user_data_updated_func_t on_user_data_updated;

public:
	UserDataListenerImplGlobal(
		on_user_data_updated_func_t on_user_data_updated = nullptr) :
		on_user_data_updated{ on_user_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserDataListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserDataUpdated() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_user_data_updated != nullptr) {
			on_user_data_updated();
		}
	}
};

class UserDataListenerImplLocal : public galaxy::api::IUserDataListener
{
public:
	using on_user_data_updated_func_t = std::function<void()>;

private:
	on_user_data_updated_func_t on_user_data_updated;

public:
	UserDataListenerImplLocal(
		on_user_data_updated_func_t on_user_data_updated = nullptr) :
		on_user_data_updated{ on_user_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserDataListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserDataUpdated() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_user_data_updated != nullptr) {
			on_user_data_updated();
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerUserDataListenerImplGlobal : public galaxy::api::GameServerGlobalUserDataListener
{
public:
	using on_user_data_updated_func_t = std::function<void()>;

private:
	on_user_data_updated_func_t on_user_data_updated;

public:
	GameServerUserDataListenerImplGlobal(
		on_user_data_updated_func_t on_user_data_updated = nullptr) :
		on_user_data_updated{ on_user_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerUserDataListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserDataUpdated() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_user_data_updated != nullptr) {
			on_user_data_updated();
		}
	}
};

#endif
