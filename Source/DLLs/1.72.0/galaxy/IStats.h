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
			LEADERBOARD_SORT_METHOD_NONE = 0, ///< No sorting method specified.
			LEADERBOARD_SORT_METHOD_ASCENDING = 1, ///< Top score is lowest number.
			LEADERBOARD_SORT_METHOD_DESCENDING = 2 ///< Top score is highest number.
		};

		/**
		 * The display type of a leaderboard.
		 */
		enum LeaderboardDisplayType
		{
			LEADERBOARD_DISPLAY_TYPE_NONE = 0, ///< Not display type specified.
			LEADERBOARD_DISPLAY_TYPE_NUMBER = 1, ///< Simple numerical score.
			LEADERBOARD_DISPLAY_TYPE_TIME_SECONDS = 2, ///< The score represents time, in seconds.
			LEADERBOARD_DISPLAY_TYPE_TIME_MILLISECONDS = 3 ///< The score represents time, in milliseconds.
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
			 * To read statistics call GetStatInt() or GetStatFloat(),
			 * depending on the type of the statistic to read.
			 *
			 * To read achievements call GetAchievement().
			 *
			 * @param userID The ID of the user.
			 */
			virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID) = 0;

			/**
			 * The reason of a failure in retrieving statistics and achievements.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in retrieving statistics
			 * and achievements for a specified user.
			 *
			 * @param userID The ID of the user.
			 * @param failureReason The cause of the failure.
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
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in storing statistics
			 * and achievements.
			 *
			 * @param failureReason The cause of the failure.
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
			// //  * @param name The code name of the achievement.
			// //  * @param currentProgress Current value of progress for the achievement.
			// //  * @param maxProgress The maximum value of progress for the achievement.
			// //  */
			// // void OnAchievementProgressChanged(const char* name, uint32_t currentProgress, uint32_t maxProgress) = 0;

			/**
			 * Notification for the event of storing changes that result in
			 * unlocking a particular achievement.
			 *
			 * @param name The code name of the achievement.
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
			 * In order to read metadata of retrieved leaderboards, call GetLeaderboardDisplayName(),
			 * GetLeaderboardSortMethod(), or GetLeaderboardDisplayType().
			 *
			 * In order to read entries, retrieve some first by calling RequestLeaderboardEntriesGlobal(),
			 * RequestLeaderboardEntriesAroundUser(), or RequestLeaderboardEntriesForUsers().
			 */
			virtual void OnLeaderboardsRetrieveSuccess() = 0;

			/**
			 * The reason of a failure in retrieving definitions of leaderboards.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in retrieving definitions of leaderboards.
			 *
			 * @param failureReason The cause of the failure.
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
			 * In order to read subsequent entries, call GetRequestedLeaderboardEntry().
			 *
			 * @param name The name of the leaderboard.
			 * @param entryCount The number of entries that were retrieved.
			 */
			virtual void OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount) = 0;

			/**
			 * The reason of a failure in retrieving requested entries of a leaderboard.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_NOT_FOUND ///< Could not find any entries for specified search criteria.
			};

			/**
			 * Notification for the event of a failure in retrieving requested entries of a leaderboard.
			 *
			 * @param name The name of the leaderboard.
			 * @param failureReason The cause of the failure.
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
			 * @param name The name of the leaderboard.
			 * @param score The score after the update.
			 * @param oldRank Previous rank, i.e. before the update; 0 if the user had no entry yet.
			 * @param newRank Current rank, i.e. after the update.
			 */
			virtual void OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank) = 0;

			/**
			 * The reason of a failure in updating score in a leaderboard.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_NO_IMPROVEMENT ///< Previous score was better and the update operation was not forced.
			};

			/**
			 * The reason of a failure in updating score in a leaderboard.
			 *
			 * @param name The name of the leaderboard.
			 * @param score The score that was attempted to set.
			 * @param failureReason The cause of the failure.
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
			* In order to read metadata of the retrieved leaderboard, call GetLeaderboardDisplayName(),
			* GetLeaderboardSortMethod(), or GetLeaderboardDisplayType().
			*
			* In order to read entries, retrieve some first by calling RequestLeaderboardEntriesGlobal(),
			* RequestLeaderboardEntriesAroundUser(), or RequestLeaderboardEntriesForUsers().
			*
			* @param name The name of the leaderboard.
			*/
			virtual void OnLeaderboardRetrieveSuccess(const char* name) = 0;

			/**
			* The reason of a failure in retrieving definition of a leaderboard.
			*/
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			* Notification for the event of a failure in retrieving definition of a leaderboard.
			*
			* @param name The name of the leaderboard.
			* @param failureReason The cause of the failure.
			*/
			virtual void OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason) = 0;
		};

		/**
		* Globally self-registering version of a ILeaderboardRetrieveListener.
		*/
		typedef SelfRegisteringListener<ILeaderboardRetrieveListener> GlobalLeaderboardRetrieveListener;

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
			 * Performs a request for statistics and achievements of specified user.
			 *
			 * This call is asynchronous. Responses come to the IUserStatsAndAchievementsRetrieveListener.
			 *
			 * @param userID The ID of the user. It can be omitted when requesting for own data.
			 */
			virtual void RequestUserStatsAndAchievements(GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Reads integer value of a statistic of specified user.
			 *
			 * @remark Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The code name of the statistic.
			 * @param userID The ID of the user. It can be omitted when requesting for own data.
			 * @return The value of the statistic.
			 */
			virtual int32_t GetStatInt(const char* name, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Reads floating point value of a statistic of specified user.
			 *
			 * @remark Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The code name of the statistic.
			 * @param userID The ID of the user. It can be omitted when requesting for own data.
			 * @return The value of the statistic.
			 */
			virtual float GetStatFloat(const char* name, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Updates a statistic with an integer value.
			 *
			 * @remark Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @param name The code name of the statistic.
			 * @param value The value of the statistic to set.
			 */
			virtual void SetStatInt(const char* name, int32_t value) = 0;

			/**
			 * Updates a statistic with a floating point value.
			 *
			 * @remark Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @param name The code name of the statistic.
			 * @param value The value of the statistic to set.
			 */
			virtual void SetStatFloat(const char* name, float value) = 0;

			/**
			 * Updates an average-rate statistic with a delta.
			 *
			 * @remark Retrieve the statistics first by calling RequestUserStatsAndAchievements().
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @param name The code name of the statistic.
			 * @param countThisSession The delta of the count.
			 * @param sessionLength The delta of the session.
			 */
			virtual void UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) = 0;

			/**
			 * Reads the state of an achievement of specified user.
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The code name of the achievement.
			 * @param unlocked Indicates if the achievement has been unlocked.
			 * @param unlockTime The time at which the achievement was unlocked.
			 * @param userID The ID of the user. It can be omitted when requesting for own data.
			 */
			virtual void GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Unlocks an achievement. The achievement is marked as unlocked at the time
			 * at which this message was called.
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @param name The code name of the achievement.
			 */
			virtual void SetAchievement(const char* name) = 0;

			/**
			 * Clears an achievement.
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 * @remark In order to make this and other changes persistent, call StoreStatsAndAchievements().
			 *
			 * @param name The code name of the achievement.
			 */
			virtual void ClearAchievement(const char* name) = 0;

			/**
			 * Persists all changes in statistics and achievements.
			 *
			 * This call is asynchronous. Responses come to the
			 * IStatsAndAchievementsStoreListener.
			 * Notifications about storing changes that result in unlocking
			 * achievements come to the IAchievementChangeListener.
			 */
			virtual void StoreStatsAndAchievements() = 0;

			/**
			 * Resets all statistics and achievements.
			 *
			 * This is the same as setting statistics and achievements to their
			 * initial values and calling StoreStatsAndAchievements().
			 *
			 * This call is asynchronous. Responses come to the
			 * IStatsAndAchievementsStoreListener.
			 */
			virtual void ResetStatsAndAchievements() = 0;

			/**
			 * Returns display name of the specified achievement.
			 *
			 * @remark This call is not thread-safe as opposed to GetAchievementDisplayNameCopy().
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The name of the achievement.
			 * @return Display name of the specified achievement.
			 */
			virtual const char* GetAchievementDisplayName(const char* name) = 0;

			/**
			 * Returns description of the specified achievement.
			 *
			 * @remark This call is not thread-safe as opposed to GetAchievementDescriptionCopy().
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The name of the achievement.
			 * @return Descirption of the scpecified achievement.
			 */
			virtual const char* GetAchievementDescription(const char* name) = 0;

			/**
			 * Returns visibility status of the specified achievement.
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The name of the achievement.
			 * @return If the achievement is visible.
			 */
			virtual bool IsAchievementVisible(const char* name) = 0;

			/**
			 * Performs a request for definitions of leaderboards.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardsRetrieveListener.
			 */
			virtual void RequestLeaderboards() = 0;

			/**
			 * Returns display name of specified leaderboard.
			 *
			 * @remark This call is not thread-safe as opposed to GetLeaderboardDisplayNameCopy().
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param name The name of the leaderboard.
			 * @return Display name of the leaderboard.
			 */
			virtual const char* GetLeaderboardDisplayName(const char* name) = 0;

			/**
			 * Copies display name of specified leaderboard.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param name The name of the leaderboard.
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 */
			virtual void GetLeaderboardDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Returns sort method of specified leaderboard.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param name The name of the leaderboard.
			 * @return Sort method of the leaderboard.
			 */
			virtual LeaderboardSortMethod GetLeaderboardSortMethod(const char* name) = 0;

			/**
			 * Returns display type of specified leaderboard.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param name The name of the leaderboard.
			 * @return Display type of the leaderboard.
			 */
			virtual LeaderboardDisplayType GetLeaderboardDisplayType(const char* name) = 0;

			/**
			 * Performs a request for entries of specified leaderboard in a global scope,
			 * i.e. without any specific users in the scope of interest.
			 *
			 * The entries are indexed by integers in the range of [0, number of entries).
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardEntriesRetrieveListener.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param name The name of the leaderboard.
			 * @param rangeStart The index postition of the entry to start with.
			 * @param rangeEnd The index postition of the entry to finish with.
			 */
			virtual void RequestLeaderboardEntriesGlobal(const char* name, uint32_t rangeStart, uint32_t rangeEnd) = 0;

			/**
			 * Performs a request for entries of specified leaderboard for and near given user.
			 *
			 * The specified numbers of entries before and after the specified user are treated as hints.
			 * If the requested range would go beyond the set of all leaderboard entries, it is shifted
			 * so that it fits in the set of all leaderboard entries and preserves its size if possible.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardEntriesRetrieveListener.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param name The name of the leaderboard.
			 * @param countBefore The number of entries placed before the user's entry to retrieve (hint).
			 * @param countAfter The number of entries placed after the user's entry to retrieve (hint).
			 * @param userID The ID of the user. It can be omitted when requesting for own data.
			 */
			virtual void RequestLeaderboardEntriesAroundUser(const char* name, uint32_t countBefore, uint32_t countAfter, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Performs a request for entries of specified leaderboard for specified users.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardEntriesRetrieveListener.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * @param name The name of the leaderboard.
			 * @param userArray An array with the list of IDs of the users in scope.
			 * @param userArraySize The size of the array, i.e. the number of users in the specified list.
			 */
			virtual void RequestLeaderboardEntriesForUsers(const char* name, GalaxyID* userArray, uint32_t userArraySize) = 0;

			/**
			 * Returns data from the currently proccessed request for leaderboard entries.
			 *
			 * Use this call to iterate over last retrieved lobby entries, indexed from 0.
			 *
			 * In order to retrieve lobbies and get their count, first you need to call
			 * RequestLeaderboardEntriesGlobal(), RequestLeaderboardEntriesAroundUser(),
			 * or RequestLeaderboardEntriesForUsers().
			 *
			 * @remark This method can be used only inside of
			 * ILeaderboardEntriesRetrieveListener::OnOnLeaderboardEntriesRetrieveSuccess().
			 *
			 * @param index Index as an integer in the range of [0, number of entries fetched).
			 * @param rank User's rank in the leaderboard.
			 * @param score User's score in the leaderboard.
			 * @param userID The ID of the user.
			 */
			virtual void GetRequestedLeaderboardEntry(uint32_t index, uint32_t& rank, int32_t& score, GalaxyID& userID) = 0;

			/**
			 * Returns data with details from the currently proccessed request for leaderboard entries.
			 *
			 * Use this call to iterate over last retrieved lobby entries, indexed from 0.
			 *
			 * In order to retrieve lobbies and get their count, first you need to call
			 * RequestLeaderboardEntriesGlobal(), RequestLeaderboardEntriesAroundUser(),
			 * or RequestLeaderboardEntriesForUsers().
			 *
			 * If the buffer that is supposed to take the details data is too small,
			 * the details will be truncated to its size.
			 *
			 * @remark This method can be used only inside of
			 * ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveSuccess().
			 *
			 * @param index Index as an integer in the range of [0, number of entries fetched).
			 * @param rank User's rank in the leaderboard.
			 * @param score User's score in the leaderboard.
			 * @param details An extra, outgoing game-defined information regarding how the user got that score.
			 * @param detailsSize The size of passed buffer of the extra game-defined information.
			 * @param outDetailsSize The size of the extra game-defined information.
			 * @param userID The ID of the user.
			 */
			virtual void GetRequestedLeaderboardEntryWithDetails(uint32_t index, uint32_t& rank, int32_t& score, void* details, uint32_t detailsSize, uint32_t& outDetailsSize, GalaxyID& userID) = 0;

			/**
			 * Updates entry for own user in the specified leaderboard.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardScoreUpdateListener.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * For this call to work while the user is logged off, the definition of the leaderboard
			 * must have been retrieved at least once while the user was logged on.
			 *
			 * @param name The name of the leaderboard.
			 * @param score The score to set.
			 * @param forceUpdate If the update should be performed in case the score is worse than the previous score.
			 */
			virtual void SetLeaderboardScore(const char* name, int32_t score, bool forceUpdate = false) = 0;

			/**
			 * Updates entry with details for own user in the specified leaderboard.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardScoreUpdateListener.
			 *
			 * @remark Retrieve definition of this particular leaderboard first by calling
			 * either FindLeaderboard() or FindOrCreateLeaderboard(), or definitions of all existing leaderboards
			 * by calling RequestLeaderboards().
			 *
			 * For this call to work while the user is logged off, the definition of the leaderboard
			 * must have been retrieved at least once while the user was logged on.
			 *
			 * @param name The name of the leaderboard.
			 * @param score The score to set.
			 * @param details An extra game-defined information regarding how the user got that score.
			 * @param detailsSize The size of buffer of the extra game-defined information.
			 * @param forceUpdate If the update should be performed in case the score is worse than the previous score.
			 */
			virtual void SetLeaderboardScoreWithDetails(const char* name, int32_t score, const void* details, uint32_t detailsSize, bool forceUpdate = false) = 0;

			/**
			 * Returns the leaderboard entry count for requested leaderboard.
			 *
			 * In order to retrieve leaderboard entry count, first you need to call
			 * RequestLeaderboardEntriesGlobal(), RequestLeaderboardEntriesAroundUser(),
			 * or RequestLeaderboardEntriesForUsers().
			 *
			 * @param name The name of the leaderboard.
			 * @return The leaderboard entry count.
			 */
			virtual uint32_t GetLeaderboardEntryCount(const char* name) = 0;

			/**
			 * Performs a request for definition of the specified leaderboard.
			 *
			 * This call is asynchronous. Responses come to the ILeaderboardRetrieveListener.
			 *
			 * @param name The name of the leaderboard.
			 */
			virtual void FindLeaderboard(const char* name) = 0;

			/**
			* Performs a request for definition of the specified leaderboard, creating it
			* if there is no such leaderboard yet.
			*
			* This call is asynchronous. Responses come to the ILeaderboardRetrieveListener.
			*
			* @remark If the leaderboard of the specified name is found, this call ends
			* with success no matter if the definition of the leaderboard matches
			* the parameters specified in the call to this method.
			*
			* @param name The name of the leaderboard.
			* @param displayName The display name of the leaderboard.
			* @param sortMethod The sort method of the leaderboard.
			* @param displayType The display method of the leaderboad.
			*/
			virtual void FindOrCreateLeaderboard(const char* name, const char* displayName, LeaderboardSortMethod sortMethod, LeaderboardDisplayType displayType) = 0;

			/**
			 * Copies display name of the specified achievement.
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The name of the achievement.
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 */
			virtual void GetAchievementDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Copies description of the specified achievement.
			 *
			 * @remark Retrieve the achievements first by calling RequestUserStatsAndAchievements().
			 *
			 * @param name The name of the achievement.
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 */
			virtual void GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) = 0;
		};

		/** @} */
	}
}

#endif
