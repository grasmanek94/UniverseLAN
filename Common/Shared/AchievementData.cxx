#include "AchievementData.hxx"

#include <chrono>
#include <string>

AchievementData::AchievementData() :
	Dirty{ false },
	Name{ "" },
	Description{ "" },
	Unlocked{ false },
	UnlockTime{ 0 },
	Visible{ true },
	VisibleWhileLocked{ true }
{}

void AchievementData::SetName(std::string name)
{
	Dirty = true;
	Name = name;
}

void AchievementData::SetDescription(std::string description)
{
	Dirty = true;
	Description = description;
}

void AchievementData::SetUnlocked(bool unlocked)
{
	Dirty = true;
	Unlocked = unlocked;
}

void AchievementData::SetUnlockTime(uint32_t unlock_time)
{
	Dirty = true;
	UnlockTime = unlock_time;
}

void AchievementData::SetUnlockTimeNow()
{
	using namespace std::chrono;

	Dirty = true;
	UnlockTime = (uint32_t)duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

void AchievementData::SetVisible(bool visible)
{
	Dirty = true;
	Visible = visible;
}

void AchievementData::SetVisibleWhileLocked(bool visible_while_locked)
{
	Dirty = true;
	VisibleWhileLocked = visible_while_locked;
}

void AchievementData::ResetDirty()
{
	Dirty = false;
}

const std::string& AchievementData::GetName() const
{
	return Name;
}

const std::string& AchievementData::GetDescription() const
{
	return Description;
}

bool AchievementData::GetUnlocked() const
{
	return Unlocked;
}

uint32_t AchievementData::GetUnlockTime() const
{
	return UnlockTime;
}

bool AchievementData::GetVisible() const
{
	return Visible;
}

bool AchievementData::GetVisibleWhileLocked() const
{
	return VisibleWhileLocked;
}

bool AchievementData::IsDirty() const
{
	return Dirty;
}
