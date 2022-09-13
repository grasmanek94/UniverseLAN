#include <chrono>
#include <thread>

#include <GalaxyApi.h>

int main()
{
	galaxy::api::InitOptions options("","");

	galaxy::api::Init(options);

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}
