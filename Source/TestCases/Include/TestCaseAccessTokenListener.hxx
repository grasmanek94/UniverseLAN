#pragma once

#include "TestCaseClientDetails.hxx"

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
class AccessTokenListenerImplGlobal : public galaxy::api::GlobalAccessTokenListener
{
public:
	using on_access_token_changed_func_t = std::function<void(void)>;

private:
	on_access_token_changed_func_t on_access_token_changed;

public:
	AccessTokenListenerImplGlobal(
		on_access_token_changed_func_t on_access_token_changed = nullptr) :
		on_access_token_changed{ on_access_token_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~AccessTokenListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAccessTokenChanged() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_access_token_changed) {
			on_access_token_changed();
		}
	}
};

class AccessTokenListenerImplLocal : public galaxy::api::IAccessTokenListener
{
public:
	using on_access_token_changed_func_t = std::function<void(void)>;

private:
	on_access_token_changed_func_t on_access_token_changed;

public:
	AccessTokenListenerImplLocal(
		on_access_token_changed_func_t on_access_token_changed = nullptr) :
		on_access_token_changed{ on_access_token_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~AccessTokenListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAccessTokenChanged() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_access_token_changed) {
			on_access_token_changed();
		}
	}
};
#endif

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerAccessTokenListenerImplGlobal : public galaxy::api::GameServerGlobalAccessTokenListener
{
public:
	using on_access_token_changed_func_t = std::function<void(void)>;

private:
	on_access_token_changed_func_t on_access_token_changed;

public:
	GameServerAccessTokenListenerImplGlobal(
		on_access_token_changed_func_t on_access_token_changed = nullptr) :
		on_access_token_changed{ on_access_token_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerAccessTokenListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAccessTokenChanged() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_access_token_changed) {
			on_access_token_changed();
		}
	}
};

#endif
