#pragma once

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER

#include "TestCaseClientDetails.hxx"

class GogServicesConnectionStateListenerImplGlobal : public galaxy::api::GlobalGogServicesConnectionStateListener
{
public:
	using on_connection_state_change_func_t = std::function<void(GogServicesConnectionState)>;

private:
	on_connection_state_change_func_t on_connection_state_change;

public:
	GogServicesConnectionStateListenerImplGlobal(
		on_connection_state_change_func_t on_connection_state_change = nullptr) :
		on_connection_state_change{ on_connection_state_change } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GogServicesConnectionStateListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionStateChange(GogServicesConnectionState connectionState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionState: {}",
			magic_enum::enum_name(connectionState)
		).c_str());


		if (on_connection_state_change != nullptr) {
			on_connection_state_change(connectionState);
		}
	}
};

class GogServicesConnectionStateListenerImplLocal : public galaxy::api::IGogServicesConnectionStateListener
{
public:
	using on_connection_state_change_func_t = std::function<void(GogServicesConnectionState)>;

private:
	on_connection_state_change_func_t on_connection_state_change;

public:
	GogServicesConnectionStateListenerImplLocal(
		on_connection_state_change_func_t on_connection_state_change = nullptr) :
		on_connection_state_change{ on_connection_state_change } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GogServicesConnectionStateListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionStateChange(GogServicesConnectionState connectionState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionState: {}",
			magic_enum::enum_name(connectionState)
		).c_str());


		if (on_connection_state_change != nullptr) {
			on_connection_state_change(connectionState);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerGogServicesConnectionStateListenerImplGlobal : public galaxy::api::GameServerGlobalGogServicesConnectionStateListener
{
public:
	using on_connection_state_change_func_t = std::function<void(GogServicesConnectionState)>;

private:
	on_connection_state_change_func_t on_connection_state_change;

public:
	GameServerGogServicesConnectionStateListenerImplGlobal(
		on_connection_state_change_func_t on_connection_state_change = nullptr) :
		on_connection_state_change{ on_connection_state_change } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerGogServicesConnectionStateListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionStateChange(GogServicesConnectionState connectionState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionState: {}",
			magic_enum::enum_name(connectionState)
		).c_str());


		if (on_connection_state_change != nullptr) {
			on_connection_state_change(connectionState);
		}
	}
};

#endif
#endif
