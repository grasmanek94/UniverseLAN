#pragma once

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM

#include "TestCaseClientDetails.hxx"

class OverlayVisibilityChangeListenerImplGlobal : public galaxy::api::GlobalOverlayVisibilityChangeListener
{
public:
	using on_overlay_visibility_changed_func_t = std::function<void(bool overlayVisible)>;

private:
	on_overlay_visibility_changed_func_t on_overlay_visibility_changed;

public:
	OverlayVisibilityChangeListenerImplGlobal(
		on_overlay_visibility_changed_func_t on_overlay_visibility_changed = nullptr) :
		on_overlay_visibility_changed{ on_overlay_visibility_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OverlayVisibilityChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOverlayVisibilityChanged(bool overlayVisible) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayVisible: {}",
			overlayVisible
		).c_str());


		if (on_overlay_visibility_changed != nullptr) {
			on_overlay_visibility_changed(overlayVisible);
		}
	}
};

class OverlayVisibilityChangeListenerImplLocal : public galaxy::api::IOverlayVisibilityChangeListener
{
public:
	using on_overlay_visibility_changed_func_t = std::function<void(bool overlayVisible)>;

private:
	on_overlay_visibility_changed_func_t on_overlay_visibility_changed;

public:
	OverlayVisibilityChangeListenerImplLocal(
		on_overlay_visibility_changed_func_t on_overlay_visibility_changed = nullptr) :
		on_overlay_visibility_changed{ on_overlay_visibility_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~OverlayVisibilityChangeListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnOverlayVisibilityChanged(bool overlayVisible) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayVisible: {}",
			overlayVisible
		).c_str());


		if (on_overlay_visibility_changed != nullptr) {
			on_overlay_visibility_changed(overlayVisible);
		}
	}
};

#endif
