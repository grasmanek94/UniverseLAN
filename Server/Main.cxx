#include "Server.hxx"

#include <Version.hxx>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

std::unique_ptr<Server> server;
int main()
{
	std::cout << "Version: " << Version_Number << std::endl;

	server = std::make_unique<Server>();
	std::chrono::milliseconds wait_time = std::chrono::milliseconds(1000 / server->GetMaxTickRate());

	while (true)
	{
		server->Tick();
		std::this_thread::sleep_for(wait_time);
	}
	return 0;
}
