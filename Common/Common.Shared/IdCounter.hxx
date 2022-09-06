#pragma once
#include <cstdlib>
#include <vector>

class IdCounter
{
	std::vector<size_t> free_ids;
	std::vector<bool> taken_ids;
public:
	IdCounter(size_t max_ids);
	size_t GetId();
	bool FreeId(size_t id);
	size_t Max();
};
