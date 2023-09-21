#pragma once

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM

#include "TestCaseClientDetails.hxx"

class OverlayInitializationStateChangeListenerImplGlobal : public galaxy::api::GlobalOverlayInitializationStateChangeListener
{
public:
	using on_overlay_state_changed_func_t = std::function<void(OverlayState)>;

private:
	on_overlay_state_changed_func_t on_overlay_state_changed;

public:
	OverlayInitializationStateChangeListenerImplGlobal(
		on_overlay_state_changed_func_t on_overlay_state_changed = nullptr) :
		on_overlay_state_changed{ on_overlay_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OverlayInitializationStateChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOverlayStateChanged(OverlayState overlayState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayState: {}",
			magic_enum::enum_name(overlayState)
		).c_str());


		if (on_overlay_state_changed != nullptr) {
			on_overlay_state_changed(overlayState);
		}
	}
};

class OverlayInitializationStateChangeListenerImplLocal : public galaxy::api::IOverlayInitializationStateChangeListener
{
public:
	using on_overlay_state_changed_func_t = std::function<void(OverlayState)>;

private:
	on_overlay_state_changed_func_t on_overlay_state_changed;

public:
	OverlayInitializationStateChangeListenerImplLocal(
		on_overlay_state_changed_func_t on_overlay_state_changed = nullptr) :
		on_overlay_state_changed{ on_overlay_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OverlayInitializationStateChangeListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOverlayStateChanged(OverlayState overlayState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayState: {}",
			magic_enum::enum_name(overlayState)
		).c_str());


		if (on_overlay_state_changed != nullptr) {
			on_overlay_state_changed(overlayState);
		}
	}
};

#endif
