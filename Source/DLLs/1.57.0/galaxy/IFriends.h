#ifndef GALAXY_I_FRIENDS_H
#define GALAXY_I_FRIENDS_H

/**
 * @file
 * Contains data structures and interfaces related to social activities.
 */

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

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
		};

		/** @} */
	}
}

#endif
