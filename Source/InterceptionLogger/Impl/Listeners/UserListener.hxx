#pragma once

#include <IUser.h>

namespace universelan::client {
	using namespace galaxy::api;

	class AuthListener : public IAuthListener
	{
	public:
		virtual void OnAuthSuccess();
		virtual void OnAuthFailure(FailureReason failureReason);
		virtual void OnAuthLost();
	};

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
	class OtherSessionStartListener : public IOtherSessionStartListener
	{
	public:
		virtual void OnOtherSessionStarted();
	};
#endif

	class OperationalStateChangeListener : public IOperationalStateChangeListener
	{
	public:
		virtual void OnOperationalStateChanged(uint32_t operationalState);
	};

	class UserDataListener : public IUserDataListener
	{
	public:
		virtual void OnUserDataUpdated();
	};

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
	class SpecificUserDataListener : public ISpecificUserDataListener
	{
	public:
		virtual void OnSpecificUserDataUpdated(GalaxyID userID);
	};
#endif

	class EncryptedAppTicketListener : public IEncryptedAppTicketListener
	{
	public:
		virtual void OnEncryptedAppTicketRetrieveSuccess();
		virtual void OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason);
	};

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	class AccessTokenListener : public IAccessTokenListener
	{
	public:
		virtual void OnAccessTokenChanged();
	};
#endif
}
