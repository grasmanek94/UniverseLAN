#include <enet6/enet.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

using namespace std::chrono;

int main()
{
	milliseconds wait_time = milliseconds(1);

	while (true)
	{
		std::this_thread::sleep_for(wait_time);
	}
	return 0;
}
