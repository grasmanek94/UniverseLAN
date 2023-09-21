#pragma once

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER

#include "TestCaseClientDetails.hxx"

class SpecificUserDataListenerImplGlobal : public galaxy::api::GlobalSpecificUserDataListener
{
public:
	using on_specific_user_data_updated_func_t = std::function<void(GalaxyID userID)>;

private:
	on_specific_user_data_updated_func_t on_specific_user_data_updated;

public:
	SpecificUserDataListenerImplGlobal(
		on_specific_user_data_updated_func_t on_specific_user_data_updated = nullptr) :
		on_specific_user_data_updated{ on_specific_user_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SpecificUserDataListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSpecificUserDataUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_specific_user_data_updated != nullptr) {
			on_specific_user_data_updated(userID);
		}
	}
};

class SpecificUserDataListenerImplLocal : public galaxy::api::ISpecificUserDataListener
{
public:
	using on_specific_user_data_updated_func_t = std::function<void(GalaxyID userID)>;

private:
	on_specific_user_data_updated_func_t on_specific_user_data_updated;

public:
	SpecificUserDataListenerImplLocal(
		on_specific_user_data_updated_func_t on_specific_user_data_updated = nullptr) :
		on_specific_user_data_updated{ on_specific_user_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SpecificUserDataListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSpecificUserDataUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_specific_user_data_updated != nullptr) {
			on_specific_user_data_updated(userID);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerSpecificUserDataListenerImplGlobal : public galaxy::api::GameServerGlobalSpecificUserDataListener
{
public:
	using on_specific_user_data_updated_func_t = std::function<void(GalaxyID userID)>;

private:
	on_specific_user_data_updated_func_t on_specific_user_data_updated;

public:
	GameServerSpecificUserDataListenerImplGlobal(
		on_specific_user_data_updated_func_t on_specific_user_data_updated = nullptr) :
		on_specific_user_data_updated{ on_specific_user_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerSpecificUserDataListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSpecificUserDataUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_specific_user_data_updated != nullptr) {
			on_specific_user_data_updated(userID);
		}
	}
};

#endif
#endif
