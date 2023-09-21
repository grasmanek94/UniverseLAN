#pragma once

#include "TestCaseClientDetails.hxx"

class PersonaDataChangedListenerImplGlobal : public galaxy::api::GlobalPersonaDataChangedListener
{
public:
	using on_persona_data_changed_func_t = std::function<void(GalaxyID, uint32_t)>;

private:
	on_persona_data_changed_func_t on_persona_data_changed;

public:
	PersonaDataChangedListenerImplGlobal(
		on_persona_data_changed_func_t on_persona_data_changed = nullptr) :
		on_persona_data_changed{ on_persona_data_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~PersonaDataChangedListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} personaStateChange: {}",
			userID, personaStateChange
		).c_str());


		if (on_persona_data_changed != nullptr) {
			on_persona_data_changed(userID, personaStateChange);
		}
	}
};

class PersonaDataChangedListenerImplLocal : public galaxy::api::IPersonaDataChangedListener
{
public:
	using on_persona_data_changed_func_t = std::function<void(GalaxyID, uint32_t)>;

private:
	on_persona_data_changed_func_t on_persona_data_changed;

public:
	PersonaDataChangedListenerImplLocal(
		on_persona_data_changed_func_t on_persona_data_changed = nullptr) :
		on_persona_data_changed{ on_persona_data_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~PersonaDataChangedListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} personaStateChange: {}",
			userID, personaStateChange
		).c_str());


		if (on_persona_data_changed != nullptr) {
			on_persona_data_changed(userID, personaStateChange);
		}
	}
};
