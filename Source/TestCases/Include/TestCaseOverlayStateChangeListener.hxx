#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IOVERLAYSTATECHANGELISTENER

#include "TestCaseClientDetails.hxx"

class OverlayStateChangeListenerImplGlobal : public galaxy::api::GlobalOverlayStateChangeListener
{
public:
	using on_overlay_state_changed_func_t = std::function<void(bool overlayIsActive)>;

private:
	on_overlay_state_changed_func_t on_overlay_state_changed;

public:
	OverlayStateChangeListenerImplGlobal(
		on_overlay_state_changed_func_t on_overlay_state_changed = nullptr) :
		on_overlay_state_changed{ on_overlay_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OverlayStateChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOverlayStateChanged(bool overlayIsActive) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayIsActive: {}",
			overlayIsActive
		).c_str());


		if (on_overlay_state_changed != nullptr) {
			on_overlay_state_changed(overlayIsActive);
		}
	}
};

class OverlayStateChangeListenerImplLocal : public galaxy::api::IOverlayStateChangeListener
{
public:
	using on_overlay_state_changed_func_t = std::function<void(bool overlayIsActive)>;

private:
	on_overlay_state_changed_func_t on_overlay_state_changed;

public:
	OverlayStateChangeListenerImplLocal(
		on_overlay_state_changed_func_t on_overlay_state_changed = nullptr) :
		on_overlay_state_changed{ on_overlay_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OverlayStateChangeListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOverlayStateChanged(bool overlayIsActive) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayIsActive: {}",
			overlayIsActive
		).c_str());


		if (on_overlay_state_changed != nullptr) {
			on_overlay_state_changed(overlayIsActive);
		}
	}
};

#endif
