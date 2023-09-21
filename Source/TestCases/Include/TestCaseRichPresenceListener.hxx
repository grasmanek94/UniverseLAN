#pragma once

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS

#include "TestCaseClientDetails.hxx"

class RichPresenceListenerImplGlobal : public galaxy::api::GlobalRichPresenceListener
{
public:
	using on_rich_presence_updated_func_t = std::function<void(GalaxyID)>;

private:
	on_rich_presence_updated_func_t on_rich_presence_updated;

public:
	RichPresenceListenerImplGlobal(
		on_rich_presence_updated_func_t on_rich_presence_updated = nullptr) :
		on_rich_presence_updated{ on_rich_presence_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~RichPresenceListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnRichPresenceUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_rich_presence_updated != nullptr) {
			on_rich_presence_updated(userID);
		}
	}
};

class RichPresenceListenerImplLocal : public galaxy::api::IRichPresenceListener
{
public:
	using on_rich_presence_updated_func_t = std::function<void(GalaxyID)>;

private:
	on_rich_presence_updated_func_t on_rich_presence_updated;

public:
	RichPresenceListenerImplLocal(
		on_rich_presence_updated_func_t on_rich_presence_updated = nullptr) :
		on_rich_presence_updated{ on_rich_presence_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~RichPresenceListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnRichPresenceUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_rich_presence_updated != nullptr) {
			on_rich_presence_updated(userID);
		}
	}
};

#endif
