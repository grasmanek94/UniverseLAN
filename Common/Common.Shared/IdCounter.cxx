#include "IdCounter.hxx"

IdCounter::IdCounter(size_t max_ids)
{
	free_ids.reserve(max_ids);
	taken_ids.resize(max_ids);
	for (size_t i = 0; i < max_ids; ++i)
	{
		free_ids.push_back((max_ids - 1) - i);
	}
}

size_t IdCounter::GetId()
{
	if (free_ids.size())
	{
		size_t free_id = free_ids.back();
		taken_ids[free_id] = true;
		free_ids.pop_back();
		return free_id;
	}
	return (size_t)-1;
}

bool IdCounter::FreeId(size_t id)
{
	if (taken_ids.size() <= id)
	{
		return false;
	}

	if (!taken_ids[id])
	{
		return false;
	}

	taken_ids[id] = false;
	free_ids.push_back(id);

	return true;
}

size_t IdCounter::Max()
{
	return taken_ids.size();
}
