#ifndef GALAXY_I_STATS_H
#define GALAXY_I_STATS_H

/**
 * @file
 * Contains data structures and interfaces related to statistics, achievements and leaderboards.
 */

#include "IListenerRegistrar.h"
#include "GalaxyID.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The sort order of a leaderboard.
		 */
		enum LeaderboardSortMethod
		{
			LEADERBOARD_SORT_METHOD_NONE, ///< No sorting method specified.
			LEADERBOARD_SORT_METHOD_ASCENDING, ///< Top score is lowest number.
			LEADERBOARD_SORT_METHOD_DESCENDING ///< Top score is highest number.
		};

		/**
		 * The display type of a leaderboard.
		 */
		enum LeaderboardDisplayType
		{
			LEADERBOARD_DISPLAY_TYPE_NONE, ///< Not display type specified.
			LEADERBOARD_DISPLAY_TYPE_NUMBER, ///< Simple numerical score.
			LEADERBOARD_DISPLAY_TYPE_TIME_SECONDS, ///< The score represents time, in seconds.
			LEADERBOARD_DISPLAY_TYPE_TIME_MILLISECONDS ///< The score represents time, in milliseconds.
		};

		/**
		 * Listener for the event of retrieving statistics and achievements
		 * of a specified user, possibly our own.
		 */
		class IUserStatsAndAchievementsRetrieveListener : public GalaxyTypeAwareListener<USER_STATS_AND_ACHIEVEMENTS_RETRIEVE>
		{
		public:

			/**
			 * Notification for the event of success in retrieving statistics
			 * and achievements for a specified user.
			 *
			 * To read statistics call IStats::GetStatInt() or IStats::GetStatFloat(),
			 * depending on the type of the statistic to read.
			 *
			 * To read achievements call IStats::GetAchievement().
			 *
			 * @param [in] userID The ID of the user.
			 */
			virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID) = 0;

			/**
			 * The reason of a failure in retrieving statistics and achievements.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in retrieving statistics
			 * and achievements for a specified user.
			 *
			 * @param [in] userID The ID of the user.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IUserStatsAndAchievementsRetrieveListener.
		 */
		typedef SelfRegisteringListener<IUserStatsAndAchievementsRetrieveListener> GlobalUserStatsAndAchievementsRetrieveListener;

		/**
		 * Listener for the event of storing own statistics and achievements.
		 */
		class IStatsAndAchievementsStoreListener : public GalaxyTypeAwareListener<STATS_AND_ACHIEVEMENTS_STORE>
		{
		public:

			/**
			 * Notification for the event of success in storing statistics
			 * and achievements.
			 */
			virtual void OnUserStatsAndAchievementsStoreSuccess() = 0;

			/**
			 * The reason of a failure in storing statistics and achievements.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in storing statistics
			 * and achievements.
			 *
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IStatsAndAchievementsStoreListener.
		 */
		typedef SelfRegisteringListener<IStatsAndAchievementsStoreListener> GlobalStatsAndAchievementsStoreListener;

		/**
		 * Listener for the event of changing an achievement.
		 */
		class IAchievementChangeListener : public GalaxyTypeAwareListener<ACHIEVEMENT_CHANGE>
		{
		public:

			// // /**
			// //  * Notification for the event of changing progress in unlocking
			// //  * a particular achievement.
			// //  *
			// //  * @param [in] name The code name of the achievement.
			// //  * @param [in] currentProgress Current value of progress for the achievement.
			// //  * @param [in] maxProgress The maximum value of progress for the achievement.
			// //  */
			// // void OnAchievementProgressChanged(const char* name, uint32_t currentProgress, uint32_t maxProgress) = 0;

			/**
			 * Notification for the event of storing changes that result in
			 * unlocking a particular achievement.
			 *
			 * @param [in] name The code name of the achievement.
			 */
			virtual void OnAchievementUnlocked(const char* name) = 0;
		};

		/**
		 * Globally self-registering version of IAchievementChangeListener.
		 */
		typedef SelfRegisteringListener<IAchievementChangeListener> GlobalAchievementChangeListener;

		/**
		 * Listener for the event of retrieving definitions of leaderboards.
		 */
		class ILeaderboardsRetrieveListener : public GalaxyTypeAwareListener<LEADERBOARDS_RETRIEVE>
		{
		public:

			/**
			 * Notification for the event of a success in retrieving definitions of leaderboards.
			 *
			 * In order to read metadata of retrieved leaderboards, call IStats::GetLeaderboardDisplayName(),
			 * IStats::GetLeaderboardSortMethod(), or IStats::GetLeaderboardDisplayType().
			 *
			 * In order to read entries, retrieve some first by calling IStats::RequestLeaderboardEntriesGlobal(),
			 * IStats::RequestLeaderboardEntriesAroundUser(), or IStats::RequestLeaderboardEntriesForUsers().
			 */
			virtual void OnLeaderboardsRetrieveSuccess() = 0;

			/**
			 * The reason of a failure in retrieving definitions of leaderboards.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in retrieving definitions of leaderboards.
			 *
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnLeaderboardsRetrieveFailure(FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of a ILeaderboardsRetrieveListener.
		 */
		typedef SelfRegisteringListener<ILeaderboardsRetrieveListener> GlobalLeaderboardsRetrieveListener;

		/**
		 * Listener for the event of retrieving requested entries of a leaderboard.
		 */
		class ILeaderboardEntriesRetrieveListener : public GalaxyTypeAwareListener<LEADERBOARD_ENTRIES_RETRIEVE>
		{
		public:

			/**
			 * Notification for the event of a success in retrieving requested entries of a leaderboard.
			 *
			 * In order to read subsequent entries, call IStats::GetRequestedLeaderboardEntry().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] entryCount The number of entries that were retrieved.
			 */
			virtual void OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount) = 0;

			/**
			 * The reason of a failure in retrieving requested entries of a leaderboard.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_NOT_FOUND, ///< Could not find any entries for specified search criteria.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in retrieving requested entries of a leaderboard.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of a ILeaderboardEntriesRetrieveListener.
		 */
		typedef SelfRegisteringListener<ILeaderboardEntriesRetrieveListener> GlobalLeaderboardEntriesRetrieveListener;

		/**
		 * Listener for the event of updating score in a leaderboard.
		 */
		class ILeaderboardScoreUpdateListener : public GalaxyTypeAwareListener<LEADERBOARD_SCORE_UPDATE_LISTENER>
		{
		public:

			/**
			 * Notification for the event of a success in setting score in a leaderboard.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] score The score after the update.
			 * @param [in] oldRank Previous rank, i.e. before the update; 0 if the user had no entry yet.
			 * @param [in] newRank Current rank, i.e. after the update.
			 */
			virtual void OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank) = 0;

			/**
			 * The reason of a failure in updating score in a leaderboard.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_NO_IMPROVEMENT, ///< Previous score was better and the update operation was not forced.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * The reason of a failure in updating score in a leaderboard.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] score The score that was attempted to set.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of a ILeaderboardScoreUpdateListener.
		 */
		typedef SelfRegisteringListener<ILeaderboardScoreUpdateListener> GlobalLeaderboardScoreUpdateListener;

		/**
		 * Listener for the event of retrieving definition of a leaderboard.
		 */
		class ILeaderboardRetrieveListener : public GalaxyTypeAwareListener<LEADERBOARD_RETRIEVE>
		{
		public:

			/**
			 * Notification for the event of a success in retrieving definition of a leaderboard.
			 *
			 * In order to read metadata of the retrieved leaderboard, call IStats::GetLeaderboardDisplayName(),
			 * IStats::GetLeaderboardSortMethod(), or IStats::GetLeaderboardDisplayType().
			 *
			 * In order to read entries, retrieve some first by calling IStats::RequestLeaderboardEntriesGlobal(),
			 * IStats::RequestLeaderboardEntriesAroundUser(), or IStats::RequestLeaderboardEntriesForUsers().
			 *
			 * @param [in] name The name of the leaderboard.
			 */
			virtual void OnLeaderboardRetrieveSuccess(const char* name) = 0;

			/**
			 * The reason of a failure in retrieving definition of a leaderboard.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in retrieving definition of a leaderboard.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of a ILeaderboardRetrieveListener.
		 */
		typedef SelfRegisteringListener<ILeaderboardRetrieveListener> GlobalLeaderboardRetrieveListener;

		/**
		 * Listener for the event of retrieving user time played.
		 */
		class IUserTimePlayedRetrieveListener : public GalaxyTypeAwareListener<USER_TIME_PLAYED_RETRIEVE>
		{
		public:

			/**
			 * Notification for the event of a success in retrieving user time played.
			 *
			 * In order to read user time played, call IStats::GetUserTimePlayed().
			 *
			 * @param [in] userID The ID of the user.
			 */
			virtual void OnUserTimePlayedRetrieveSuccess(GalaxyID userID) = 0;

			/**
			 * The reason of a failure in retrieving user time played.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CONNECTION_FAILURE ///< Unable to communicate with backend services.
			};

			/**
			 * Notification for the event of a failure in retrieving user time played.
			 *
			 * @param [in] userID The ID of the user.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of a IUserTimePlayedRetrieveListener.
		 */
		typedef SelfRegisteringListener<IUserTimePlayedRetrieveListener> GlobalUserTimePlayedRetrieveListener;

		/**
		 * The interface for managing statistics, achievements and leaderboards.
		 */
		class IStats
		{
		public:

			virtual ~IStats()
			{
			}

			/**
			 * Performs a request for statistics and achievements of a specified user.
			 *
			 * This call is asynchronous. Responses come to the IUserStatsAndAchievementsRetrieveListener
			 * (for all GlobalUserStatsAndAchievementsRetrieveListener-derived and optional listener passed as argument).
			 *
			 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestUserStatsAndAchievements(GalaxyID userID = GalaxyID(), IUserStatsAndAchievementsRetrieveListener* const listener = NULL) = 0;

			/**
			 * Reads integer value of a statistic of a specified user.
			 *
			 * @pre Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the statistic.
			 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
			 * @return The value of the statistic.
			 */
			virtual int32_t GetStatInt(const char* name, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Reads floating point value of a statistic of a specified user.
			 *
			 * @pre Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the statistic.
			 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
			 * @return The value of the statistic.
			 */
			virtual float GetStatFloat(const char* name, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Updates a statistic with an integer value.
			 *
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @pre Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the statistic.
			 * @param [in] value The value of the statistic to set.
			 */
			virtual void SetStatInt(const char* name, int32_t value) = 0;

			/**
			 * Updates a statistic with a floating point value.
			 *
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @pre Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the statistic.
			 * @param [in] value The value of the statistic to set.
			 */
			virtual void SetStatFloat(const char* name, float value) = 0;

			/**
			 * Updates an average-rate statistic with a delta.
			 *
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @pre Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the statistic.
			 * @param [in] countThisSession The delta of the count.
			 * @param [in] sessionLength The delta of the session.
			 */
			virtual void UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) = 0;

			/**
			 * Returns a number of achievements.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 */
			virtual uint32_t GetAchievementsNumber() = 0;

			/**
			 * Returns the 'API KEY' for an achievement index between 0 and GetAchievementsNumber.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] index The index of the achievement.
			 */
			virtual const char* GetAchievementName(uint32_t index) = 0;

			/**
			 * Copies the 'API KEY' for an achievement index between 0 and GetAchievementsNumber.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] index The index of the achievement.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetAchievementNameCopy(uint32_t index, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Reads the state of an achievement of a specified user.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the achievement.
			 * @param [in, out] unlocked Indicates if the achievement has been unlocked.
			 * @param [out] unlockTime The time at which the achievement was unlocked.
			 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
			 */
			virtual void GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Unlocks an achievement. The achievement is marked as unlocked at the time
			 * at which this message was called.
			 *
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the achievement.
			 */
			virtual void SetAchievement(const char* name) = 0;

			/**
			 * Clears an achievement.
			 *
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The code name of the achievement.
			 */
			virtual void ClearAchievement(const char* name) = 0;

			/**
			 * Persists all changes in statistics and achievements.
			 *
			 * This call is asynchronous. Responses come to the IStatsAndAchievementsStoreListener
			 * (for all GlobalStatsAndAchievementsStoreListener-derived and optional listener passed as argument).
			 *
			 * @remark Notifications about storing changes that result in unlocking
			 * achievements come to the IAchievementChangeListener.
			 *
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void StoreStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener = NULL) = 0;

			/**
			 * Resets all statistics and achievements.
			 *
			 * This is the same as setting statistics and achievements to their
			 * initial values and calling StoreStatsAndAchievements().
			 *
			 * This call is asynchronous. Responses come to the IStatsAndAchievementsStoreListener
			 * (for all GlobalStatsAndAchievementsStoreListener-derived and optional listener passed as argument).
			 *
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void ResetStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener = NULL) = 0;

			/**
			 * Returns display name of a specified achievement.
			 *
			 * @remark This call is not thread-safe as opposed to GetAchievementDisplayNameCopy().
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The name of the achievement.
			 * @return Display name of the specified achievement.
			 */
			virtual const char* GetAchievementDisplayName(const char* name) = 0;

			/**
			 * Copies display name of a specified achievement.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The name of the achievement.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetAchievementDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Returns description of a specified achievement.
			 *
			 * @remark This call is not thread-safe as opposed to GetAchievementDescriptionCopy().
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The name of the achievement.
			 * @return Description of the specified achievement.
			 */
			virtual const char* GetAchievementDescription(const char* name) = 0;

			/**
			 * Copies description of a specified achievement.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The name of the achievement.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Returns visibility status of a specified achievement.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The name of the achievement.
			 * @return If the achievement is visible.
			 */
			virtual bool IsAchievementVisible(const char* name) = 0;

			/**
			 * Returns visibility status of a specified achievement before unlocking.
			 *
			 * @pre Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param [in] name The name of the achievement.
			 * @return If the achievement is visible before unlocking.
			 */
			virtual bool IsAchievementVisibleWhileLocked(const char* name) = 0;

			/**
			 * Performs a request for definitions of leaderboards.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardsRetrieveListener.
			 *
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestLeaderboards(ILeaderboardsRetrieveListener* const listener = NULL) = 0;

			/**
			 * Returns display name of a specified leaderboard.
			 *
			 * @remark This call is not thread-safe as opposed to GetLeaderboardDisplayNameCopy().
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @return Display name of the leaderboard.
			 */
			virtual const char* GetLeaderboardDisplayName(const char* name) = 0;

			/**
			 * Copies display name of a specified leaderboard.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetLeaderboardDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Returns sort method of a specified leaderboard.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @return Sort method of the leaderboard.
			 */
			virtual LeaderboardSortMethod GetLeaderboardSortMethod(const char* name) = 0;

			/**
			 * Returns display type of a specified leaderboard.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @return Display type of the leaderboard.
			 */
			virtual LeaderboardDisplayType GetLeaderboardDisplayType(const char* name) = 0;

			/**
			 * Performs a request for entries of a specified leaderboard in a global scope,
			 * i.e. without any specific users in the scope of interest.
			 *
			 * The entries are indexed by integers in the range of [0, number of entries).
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardEntriesRetrieveListener.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] rangeStart The index position of the entry to start with.
			 * @param [in] rangeEnd The index position of the entry to finish with.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestLeaderboardEntriesGlobal(
				const char* name,
				uint32_t rangeStart,
				uint32_t rangeEnd,
				ILeaderboardEntriesRetrieveListener* const listener = NULL) = 0;

			/**
			 * Performs a request for entries of a specified leaderboard for and near the specified user.
			 *
			 * The specified numbers of entries before and after the specified user are treated as hints.
			 * If the requested range would go beyond the set of all leaderboard entries, it is shifted
			 * so that it fits in the set of all leaderboard entries and preserves its size if possible.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardEntriesRetrieveListener.
			 *
			 * @remark This call will end with failure in case there is no entry for the specified user
			 * in the specified leaderboard.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] countBefore The number of entries placed before the user's entry to retrieve (hint).
			 * @param [in] countAfter The number of entries placed after the user's entry to retrieve (hint).
			 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestLeaderboardEntriesAroundUser(
				const char* name,
				uint32_t countBefore,
				uint32_t countAfter,
				GalaxyID userID = GalaxyID(),
				ILeaderboardEntriesRetrieveListener* const listener = NULL) = 0;

			/**
			 * Performs a request for entries of a specified leaderboard for specified users.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardEntriesRetrieveListener.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] userArray An array with the list of IDs of the users in scope.
			 * @param [in] userArraySize The size of the array, i.e. the number of users in the specified list.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestLeaderboardEntriesForUsers(
				const char* name,
				GalaxyID* userArray,
				uint32_t userArraySize,
				ILeaderboardEntriesRetrieveListener* const listener = NULL) = 0;

			/**
			 * Returns data from the currently processed request for leaderboard entries.
			 *
			 * Use this call to iterate over last retrieved leaderboard entries, indexed from 0.
			 *
			 * @remark This method can be used only inside of
			 * ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveSuccess().
			 *
			 * @pre In order to retrieve lobbies and get their count, first you need to call
			 * RequestLeaderboardEntriesGlobal(), RequestLeaderboardEntriesAroundUser(),
			 * or RequestLeaderboardEntriesForUsers().
			 *
			 * @param [in] index Index as an integer in the range of [0, number of entries fetched).
			 * @param [out] rank User's rank in the leaderboard.
			 * @param [out] score User's score in the leaderboard.
			 * @param [out] userID The ID of the user.
			 */
			virtual void GetRequestedLeaderboardEntry(uint32_t index, uint32_t& rank, int32_t& score, GalaxyID& userID) = 0;

			/**
			 * Returns data with details from the currently processed request for leaderboard entries.
			 *
			 * Use this call to iterate over last retrieved leaderboard entries, indexed from 0.
			 *
			 * If the buffer that is supposed to take the details data is too small,
			 * the details will be truncated to its size.
			 *
			 * @pre In order to retrieve lobbies and get their count, first you need to call
			 * RequestLeaderboardEntriesGlobal(), RequestLeaderboardEntriesAroundUser(),
			 * or RequestLeaderboardEntriesForUsers().
			 *
			 * @remark This method can be used only inside of
			 * ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveSuccess().
			 *
			 * @param [in] index Index as an integer in the range of [0, number of entries fetched).
			 * @param [out] rank User's rank in the leaderboard.
			 * @param [out] score User's score in the leaderboard.
			 * @param [in, out] details An extra, outgoing game-defined information regarding how the user got that score.
			 * @param [in] detailsSize The size of passed buffer of the extra game-defined information.
			 * @param [out] outDetailsSize The size of the extra game-defined information.
			 * @param [out] userID The ID of the user.
			 */
			virtual void GetRequestedLeaderboardEntryWithDetails(
				uint32_t index,
				uint32_t& rank,
				int32_t& score,
				void* details,
				uint32_t detailsSize,
				uint32_t& outDetailsSize,
				GalaxyID& userID) = 0;

			/**
			 * Updates entry for own user in a specified leaderboard.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardScoreUpdateListener.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @pre For this call to work while the user is logged off, the definition of the leaderboard
			 * must have been retrieved at least once while the user was logged on.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] score The score to set.
			 * @param [in] forceUpdate If the update should be performed in case the score is worse than the previous score.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void SetLeaderboardScore(
				const char* name,
				int32_t score,
				bool forceUpdate = false,
				ILeaderboardScoreUpdateListener* const listener = NULL) = 0;

			/**
			 * Updates entry with details for own user in a specified leaderboard.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardScoreUpdateListener.
			 *
			 * @pre Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @pre For this call to work while the user is logged off, the definition of the leaderboard
			 * must have been retrieved at least once while the user was logged on.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] score The score to set.
			 * @param [in] details An extra game-defined information regarding how the user got that score with the limit of 3071 bytes.
			 * @param [in] detailsSize The size of buffer of the extra game-defined information.
			 * @param [in] forceUpdate If the update should be performed in case the score is worse than the previous score.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void SetLeaderboardScoreWithDetails(
				const char* name,
				int32_t score,
				const void* details,
				uint32_t detailsSize,
				bool forceUpdate = false,
				ILeaderboardScoreUpdateListener* const listener = NULL) = 0;

			/**
			 * Returns the leaderboard entry count for requested leaderboard.
			 *
			 * @pre In order to retrieve leaderboard entry count, first you need to call
			 * RequestLeaderboardEntriesGlobal(), RequestLeaderboardEntriesAroundUser(),
			 * or RequestLeaderboardEntriesForUsers().
			 *
			 * @param [in] name The name of the leaderboard.
			 * @return The leaderboard entry count.
			 */
			virtual uint32_t GetLeaderboardEntryCount(const char* name) = 0;

			/**
			 * Performs a request for definition of a specified leaderboard.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardRetrieveListener.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void FindLeaderboard(const char* name, ILeaderboardRetrieveListener* const listener = NULL) = 0;

			/**
			 * Performs a request for definition of a specified leaderboard, creating it
			 * if there is no such leaderboard yet.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardRetrieveListener.
			 *
			 * @remark If the leaderboard of the specified name is found, this call ends
			 * with success no matter if the definition of the leaderboard matches
			 * the parameters specified in the call to this method.
			 *
			 * @param [in] name The name of the leaderboard.
			 * @param [in] displayName The display name of the leaderboard.
			 * @param [in] sortMethod The sort method of the leaderboard.
			 * @param [in] displayType The display method of the leaderboard.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void FindOrCreateLeaderboard(
				const char* name,
				const char* displayName,
				const LeaderboardSortMethod& sortMethod,
				const LeaderboardDisplayType& displayType,
				ILeaderboardRetrieveListener* const listener = NULL) = 0;

			/**
			 * Performs a request for user time played.
			 *
			 * This call is asynchronous. Responses come to the IUserTimePlayedRetrieveListener.
			 *
			 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestUserTimePlayed(GalaxyID userID = GalaxyID(), IUserTimePlayedRetrieveListener* const listener = NULL) = 0;

			/**
			 * Reads the number of seconds played by a specified user.
			 *
			 * @pre Retrieve the statistics first by calling RequestUserTimePlayed().
			 *
			 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
			 * @return The number of seconds played by the specified user.
			 */
			virtual uint32_t GetUserTimePlayed(GalaxyID userID = GalaxyID()) = 0;
		};

		/** @} */
	}
}

#endif
