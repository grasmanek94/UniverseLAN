#include "Server.hxx"

#include <Version.hxx>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

using namespace universelan::server;
using namespace std::chrono;

std::unique_ptr<Server> server;

int main()
{
	std::cout << "Version: " << universelan::Version_Number << std::endl;

	server = std::make_unique<Server>();
	milliseconds wait_time = milliseconds(1000 / server->GetMaxTickRate());

	while (true)
	{
		server->Tick();
		std::this_thread::sleep_for(wait_time);
	}
	return 0;
}
