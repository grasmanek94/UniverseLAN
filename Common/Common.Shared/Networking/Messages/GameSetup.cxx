#include "GameSetup.hxx"

GameSetup::GameSetup(size_t id)
{
	player_id = id;
}

size_t GameSetup::GetId() const
{
	return player_id;
}

void GameSetup::SetId(size_t id)
{
	player_id = id;
}