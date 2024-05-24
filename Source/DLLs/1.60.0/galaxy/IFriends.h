#ifndef GALAXY_I_FRIENDS_H
#define GALAXY_I_FRIENDS_H

/**
 * @file
 * Contains data structures and interfaces related to social activities.
 */

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
		 * The type of avatar.
		 */
		enum AvatarType
		{
			SMALL = 0,
			SMALL_HIGH_RESOLUTION,
			MEDIUM,
			MEDIUM_HIGH_RESOLUTION,
			LARGE,
			LARGE_HIGH_RESOLUTION
		};

		/**
		 * The interface for managing social info and activities.
		 */
		class IFriends
		{
		public:

			virtual ~IFriends()
			{
			}

			/**
			 * Returns the user's nickname.
			 *
			 * @return The nickname of the user.
			 */
			virtual const char* GetPersonaName() = 0;

			/**
			 * Returns the nickname of specified user.
			 *
			 * @param userID The ID of the user.
			 * @return The nickname of the user.
			 */
			virtual const char* GetFriendPersonaName(GalaxyID userID) = 0;

			/**
			 * Returns URL of the avatar of specified user.
			 *
			 *@param userID The ID of the user.
			 *@param avatarType The type of avatar.
			 *@return The URL to the avatar.
			 */
			virtual const char* GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) = 0;
		};

		/** @} */
	}
}

#endif
