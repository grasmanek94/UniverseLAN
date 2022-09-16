#include "IdCounter.hxx"

IdCounter::IdCounter()
	: max_id(0)
{
}

uint64_t IdCounter::GetNewId()
{
	if (!free_ids.empty())
	{
		uint64_t free_id = *free_ids.begin();
		free_ids.erase(free_ids.begin());
		return free_id;
	}

	return ++max_id;
}

bool IdCounter::FreeId(uint64_t id)
{
	if (id == 0) {
		return false;
	}

	if (id >= max_id)
	{
		return false;
	}

	if (id == (max_id - 1)) {
		--max_id;
		return true;
	}

	free_ids.insert(id);

	return true;
}

uint64_t IdCounter::GetCurrentMaxId()
{
	return max_id;
}
