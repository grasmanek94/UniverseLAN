#pragma once

#include <cstdint>
#include <string>

namespace universelan {
	class AchievementData {
	private:
		bool Dirty;
		std::string Name;
		std::string Description;
		bool Unlocked;
		uint32_t UnlockTime;
		bool Visible;
		bool VisibleWhileLocked;

	public:
		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(Name, Description, Unlocked, UnlockTime, Visible, VisibleWhileLocked);
		}

		AchievementData();

		void SetName(std::string name);
		void SetDescription(std::string description);
		void SetUnlocked(bool unlocked);
		void SetUnlockTime(uint32_t unlock_time);
		void SetUnlockTimeNow();
		void SetVisible(bool visible);
		void SetVisibleWhileLocked(bool visible_while_locked);
		void ResetDirty();

		const std::string& GetName() const;
		const std::string& GetDescription() const;
		bool GetUnlocked() const;
		uint32_t GetUnlockTime() const;
		bool GetVisible() const;
		bool GetVisibleWhileLocked() const;
		bool IsDirty() const;
	};
}
