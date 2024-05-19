#if !GALAXY_BUILD_FEATURE_IUSER_GET_DATA_ACCESSTOKEN_COPY
int main() { return 0; }
#else

#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

void perform_test() {
	char access_token[1024];
	access_token[0] = '\0';

	auto user_ptr = GET_GALAXY_API(User());
	user_ptr->GetAccessTokenCopy(access_token, sizeof(access_token));

	auto si = user_ptr->SignedIn();
	auto lo = false; //user_ptr->IsLoggedOn();
	auto gid = user_ptr->GetGalaxyID();
	auto iuda =
#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
		user_ptr->IsUserDataAvailable();
#else
		false;
#endif

	auto gudc = 0; //user_ptr->GetUserDataCount();

	tracer::Trace::write_all(
		std::format(
			"SignedIn: {} IsLoggedOn: {} GetAccessToken: {} GetGalaxyID: {} IsUserDataAvailable: {} GetUserDataCount: {}",
			si,
			lo,
			access_token,
			gid,
			iuda,
			gudc
		).c_str());
}

void register_listeners() {}
bool should_keep_running() { return true; }

#endif
