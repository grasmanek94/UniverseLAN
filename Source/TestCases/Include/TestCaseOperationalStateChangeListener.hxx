#pragma once

#include "TestCaseClientDetails.hxx"

class OperationalStateChangeListenerImplGlobal : public galaxy::api::GlobalOperationalStateChangeListener
{
public:
	using on_operational_state_changed_func_t = std::function<void(uint32_t operationalState)>;

private:
	on_operational_state_changed_func_t on_operational_state_changed;

public:
	OperationalStateChangeListenerImplGlobal(
		on_operational_state_changed_func_t on_operational_state_changed = nullptr) :
		on_operational_state_changed{ on_operational_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OperationalStateChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOperationalStateChanged(uint32_t operationalState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"operationalState: {}",
			operationalState
		).c_str());


		if (on_operational_state_changed != nullptr) {
			on_operational_state_changed(operationalState);
		}
	}
};

class OperationalStateChangeListenerImplLocal : public galaxy::api::IOperationalStateChangeListener
{
public:
	using on_operational_state_changed_func_t = std::function<void(uint32_t operationalState)>;

private:
	on_operational_state_changed_func_t on_operational_state_changed;

public:
	OperationalStateChangeListenerImplLocal(
		on_operational_state_changed_func_t on_operational_state_changed = nullptr) :
		on_operational_state_changed{ on_operational_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OperationalStateChangeListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOperationalStateChanged(uint32_t operationalState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"operationalState: {}",
			operationalState
		).c_str());


		if (on_operational_state_changed != nullptr) {
			on_operational_state_changed(operationalState);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerOperationalStateChangeListenerImplGlobal : public galaxy::api::GameServerGlobalOperationalStateChangeListener
{
public:
	using on_operational_state_changed_func_t = std::function<void(uint32_t operationalState)>;

private:
	on_operational_state_changed_func_t on_operational_state_changed;

public:
	GameServerOperationalStateChangeListenerImplGlobal(
		on_operational_state_changed_func_t on_operational_state_changed = nullptr) :
		on_operational_state_changed{ on_operational_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerOperationalStateChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOperationalStateChanged(uint32_t operationalState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"operationalState: {}",
			operationalState
		).c_str());


		if (on_operational_state_changed != nullptr) {
			on_operational_state_changed(operationalState);
		}
	}
};

#endif
