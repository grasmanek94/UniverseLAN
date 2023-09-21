#pragma once

#include "TestCaseClientDetails.hxx"

class AchievementChangeListenerImplGlobal : public galaxy::api::GlobalAchievementChangeListener
{
public:
	using on_achievement_unlocked_func_t = std::function<void(const char* name)>;

private:
	on_achievement_unlocked_func_t on_achievement_unlocked;

public:
	AchievementChangeListenerImplGlobal(
		on_achievement_unlocked_func_t on_achievement_unlocked = nullptr) :
		on_achievement_unlocked{ on_achievement_unlocked } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~AchievementChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAchievementUnlocked(const char* name) {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_achievement_unlocked) {
			on_achievement_unlocked(name);
		}
	}
};

class AchievementChangeListenerImplLocal : public galaxy::api::IAchievementChangeListener
{
public:
	using on_achievement_unlocked_func_t = std::function<void(const char* name)>;

private:
	on_achievement_unlocked_func_t on_achievement_unlocked;

public:
	AchievementChangeListenerImplLocal(
		on_achievement_unlocked_func_t on_achievement_unlocked = nullptr) :
		on_achievement_unlocked{ on_achievement_unlocked } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~AchievementChangeListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAchievementUnlocked(const char* name) {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_achievement_unlocked) {
			on_achievement_unlocked(name);
		}
	}
};
