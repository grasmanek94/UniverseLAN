#include "IdCounter.hxx"

IdCounter::IdCounter()
	: max_id(0)
{
}

size_t IdCounter::GetNewId()
{
	if (!free_ids.empty())
	{
		size_t free_id = *free_ids.begin();
		free_ids.erase(free_ids.begin());
		return free_id;
	}

	return ++max_id;
}

bool IdCounter::FreeId(size_t id)
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

size_t IdCounter::GetCurrentMaxId()
{
	return max_id;
}
