#pragma once

#include "ProxifySingleShotListener.hxx"

#include <IUser.h>

namespace universelan::client {
	using namespace galaxy::api;

	class AuthListener : public IAuthListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(AuthListener, IAuthListener);

	public:
		virtual void OnAuthSuccess();
		virtual void OnAuthFailure(FailureReason failureReason);
		virtual void OnAuthLost();
	};

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
	class OtherSessionStartListener : public IOtherSessionStartListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(OtherSessionStartListener, IOtherSessionStartListener);

	public:
		virtual void OnOtherSessionStarted();
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_OPERATIONALSTATECHANGELISTENER
	class OperationalStateChangeListener : public IOperationalStateChangeListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(OperationalStateChangeListener, IOperationalStateChangeListener);

	public:
		virtual void OnOperationalStateChanged(uint32_t operationalState);
	};
#endif

	class UserDataListener : public IUserDataListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(UserDataListener, IUserDataListener);

	public:
		virtual void OnUserDataUpdated();
	};

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
	class SpecificUserDataListener : public ISpecificUserDataListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(SpecificUserDataListener, ISpecificUserDataListener);

	public:
		virtual void OnSpecificUserDataUpdated(GalaxyID userID);
	};
#endif

#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET
	class EncryptedAppTicketListener : public IEncryptedAppTicketListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(EncryptedAppTicketListener, IEncryptedAppTicketListener);

	public:
		virtual void OnEncryptedAppTicketRetrieveSuccess();
		virtual void OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	class AccessTokenListener : public IAccessTokenListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(AccessTokenListener, IAccessTokenListener);

	public:
		virtual void OnAccessTokenChanged();
	};
#endif
}
