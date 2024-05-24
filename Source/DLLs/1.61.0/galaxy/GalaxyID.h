#ifndef GALAXY_GALAXY_ID_H
#define GALAXY_GALAXY_ID_H

/**
 * @file
 * Contains GalaxyID, which is the class that represents the ID of an entity
 * used by Galaxy Peer.
 */

#include "stdint.h"
#include <assert.h>

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

#pragma pack( push, 1 )

		/**
		 * Represents the ID of an entity used by Galaxy Peer.
		 *
		 * This can be the ID of either a lobby or a Galaxy user.
		 */
		class GalaxyID
		{
		public:

			/**
			 * The numerical value used when the instance of GalaxyID is not valid.
			 */
			static const uint64_t UNASSIGNED_VALUE = 0;

			/**
			 * Default constructor.
			 *
			 * Creates an instance of GalaxyID that is invalid and of unknown kind.
			 */
			GalaxyID(void) : value(UNASSIGNED_VALUE)
			{
			}

			/**
			 * Creates an instance of GalaxyID of specified value.
			 *
			 * @param _value The numerical value of the ID.
			 */
			GalaxyID(uint64_t _value) : value(_value)
			{
			}

			/**
			 * Copy constructor.
			 *
			 * Creates a copy of another instance of GalaxyID.
			 *
			 * @param galaxyID The instance of GalaxyID to copy from.
			 */
			GalaxyID(const GalaxyID& galaxyID) : value(galaxyID.value)
			{
			}

			/**
			 * The assignment operator. Makes the ID equal to another ID.
			 *
			 * @param other The instance of GalaxyID to copy from.
			 * @return A reference to this ID.
			 */
			GalaxyID& operator=(const GalaxyID& other)
			{
				value = other.value;
				return *this;
			}

			/**
			 * The lower operator. It is supposed to be used to compare only valid
			 * instances of GalaxyID that are assigned to entities of the same type.
			 *
			 * @param other Another instance of GalaxyID to compare to.
			 * @return true if this instance is lower, false otherwise.
			 */
			bool operator<(const GalaxyID& other) const
			{
				assert(IsValid() && other.IsValid());
				return value < other.value;
			}

			/**
			 * The equality operator. Might be used to compare all sorts of GalaxyID.
			 *
			 * @param other Another instance of GalaxyID to compare to.
			 * @return true if the instances are equal, false otherwise.
			 */
			bool operator==(const GalaxyID& other) const
			{
				return value == other.value;
			}

			/**
			 * The inequality operator. The opposite to the equality operator.
			 *
			 * @param other Another instance of GalaxyID to compare to.
			 * @return false if the instances are equal, true otherwise.
			 */
			bool operator!=(const GalaxyID& other) const
			{
				return !(*this == other);
			}

			/**
			 * Checks if the ID is valid and is assigned to an entity.
			 *
			 * @return true if the ID is valid, false otherwise.
			 */
			bool IsValid() const
			{
				return value != UNASSIGNED_VALUE;
			}

			/**
			 * Returns the numerical value of the ID.
			 *
			 * @return The numerical value of the ID, valid only when the ID is valid.
			 */
			uint64_t ToUint64() const
			{
				return value;
			}

		private:

			uint64_t value; ///< The numerical value of the ID.
		};

#pragma pack( pop )

		/** @} */
	}
}

#endif
