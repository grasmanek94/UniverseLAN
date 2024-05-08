#include "Server.hxx"

#include <Tracer.hxx>
#include <Version.hxx>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#ifdef _WIN32
#include <consoleapi2.h>
#endif

using namespace universelan::tracer;
using namespace universelan::server;
using namespace std::chrono;

std::unique_ptr<Server> server;

int main()
{
	Trace trace_main{  };

	std::cout << "Build: " << universelan::Version_Number << std::endl;

#ifdef _WIN32
	SetConsoleTitleA(("UniverseLAN Server - Build: " + std::to_string(universelan::Version_Number)).c_str());
#endif

	server = std::make_unique<Server>();
	milliseconds wait_time = milliseconds(1000 / server->GetMaxTickRate());

	while (true)
	{
		server->Tick();
		std::this_thread::sleep_for(wait_time);
	}
	return 0;
}
