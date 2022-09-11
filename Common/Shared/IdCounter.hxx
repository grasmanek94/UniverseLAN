#pragma once
#include <cstdlib>
#include <set>

/* 
 * Counts ids from 1 (id 0 = invalid)
 */
class IdCounter
{
	size_t max_id;
	std::set<size_t> free_ids;
public:
	IdCounter();
	size_t GetNewId();
	bool FreeId(size_t id);
	size_t GetCurrentMaxId();
};
