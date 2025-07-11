#if GALAXY_BUILD_FEATURE_HAS_IGALAXY

#define CLIENT_FACTORY

#include <GalaxyApi.h>

#if !GALAXY_BUILD_FEATURE_FACTORY_HAS_CALLTYPE
#define FACTORY_CALLTYPE 
#else
#define FACTORY_CALLTYPE GALAXY_CALLTYPE
#endif

namespace galaxy::api
{
#if GALAXY_BUILD_FEATURE_HAS_IERRORMANAGER
	class ErrorManager : public IErrorManager {
	public:
		virtual ~ErrorManager() override {}

		ErrorManager() {}

		virtual api::IError* GetLastError() override {
			return nullptr;
		}
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IERRORMANAGER
	IErrorManager* GalaxyFactory::errorManager{ nullptr };
#endif

	IGalaxy* FACTORY_CALLTYPE GalaxyFactory::GetInstance() {
		return nullptr;
	}

#if GALAXY_BUILD_FEATURE_HAS_IERRORMANAGER
	IErrorManager* FACTORY_CALLTYPE GalaxyFactory::GetErrorManager() {
		return nullptr;
	}
#endif

#if GALAXY_BUILD_FEATURE_FACTORY_RESET_RENAMED_TO_RESETINSTANCE
	void FACTORY_CALLTYPE GalaxyFactory::ResetInstance()
#else
	void FACTORY_CALLTYPE GalaxyFactory::Reset()
#endif
	{}

	IGalaxy* FACTORY_CALLTYPE GalaxyFactory::CreateInstance() {
		return nullptr;
	}
}

#endif
