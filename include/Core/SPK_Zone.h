//////////////////////////////////////////////////////////////////////////////////
// SPARK particle engine														//
// Copyright (C) 2008-2009 - Julien Fryer - julienfryer@gmail.com				//
//																				//
// This software is provided 'as-is', without any express or implied			//
// warranty.  In no event will the authors be held liable for any damages		//
// arising from the use of this software.										//
//																				//
// Permission is granted to anyone to use this software for any purpose,		//
// including commercial applications, and to alter it and redistribute it		//
// freely, subject to the following restrictions:								//
//																				//
// 1. The origin of this software must not be misrepresented; you must not		//
//    claim that you wrote the original software. If you use this software		//
//    in a product, an acknowledgment in the product documentation would be		//
//    appreciated but is not required.											//
// 2. Altered source versions must be plainly marked as such, and must not be	//
//    misrepresented as being the original software.							//
// 3. This notice may not be removed or altered from any source distribution.	//
//////////////////////////////////////////////////////////////////////////////////


#ifndef H_SPK_ZONE
#define H_SPK_ZONE

#include "Core/SPK_DEF.h"
#include "Core/SPK_Registerable.h"
#include "Core/SPK_Transformable.h"
#include "Core/SPK_Vector3D.h"


namespace SPK
{
    class Particle;

	/**
	* @class Zone
	* @brief An abstract class that defines a zone in space
	*
	* A Zone is used in SPARK to :
	* <ul>
	* <li>define the area of an Emitter</li>
	* <li>define the area of a Modifier</li>
	* </ul>
	*/
	class SPK_PREFIX Zone : public Registerable, public Transformable
	{
	public :

		/////////////////
		// Constructor //
		/////////////////

		/**
		* @brief Default constructor for Zone
		* @param position : the position of the Zone
		*/
		Zone(const vec3& position = vec3());

		////////////////
		// Destructor //
		////////////////

		/** @brief Destructor of Zone */
		virtual ~Zone() {}

		////////////
		// Setter //
		////////////

		/**
		* @brief Sets the position of this Zone
		* @param v : the position of this Zone
		*/
		virtual void setPosition(const vec3& v);

		/////////////
		// Getters //
		/////////////

		/**
		* @brief Gets the position of this Zone
		* @return the position of this Zone
		*/
		const vec3& getPosition() const;

		/**
		* @brief Gets the transformed position of this Zone
		* @return the transformed position of this Zone
		* @since 1.03.00
		*/
		const vec3& getTransformedPosition() const;

		///////////////
		// Interface //
		///////////////

		/**
		* @brief Randomly generates a position inside this Zone for a given Particle
		* @param particle : the Particle whose position will be generated
		* @param full : true to generate a position in the whole volume of this Zone, false to generate a position only at borders
		*/
		virtual void generatePosition(Particle& particle,bool full) const = 0;

		/**
		* @brief Checks whether a point is within the Zone
		* @param point : the point to check
		* @return true if the point is within the Zone, false otherwise
		*/
		virtual bool contains(const vec3& point) const = 0;

		/**
		* @brief Checks whether a line intersects the Zone
		*
		* The intersection is computed only if the vec3* intersection is not NULL.<br>
		* The normal is computed if the vec3* normal AND intersection are not NULL.
		*
		* @param v0 : start of the line
		* @param v1 : end of the line
		* @param intersection : the vec3 where the intersection will be stored, NULL not to compute the intersection
		* @param normal : the vec3 where the normal will be stored, NULL not to compute the normal
		* @return true if the line intersects with the Zone, false otherwise
		*/
		virtual bool intersects(const vec3& v0,const vec3& v1,vec3* intersection,vec3* normal) const = 0;

		/**
		* @brief Moves a point at the border of the Zone
		* @param point : the point that will be moved to the border of the Zone
		* @param inside : true to move the point inside the Zone of APPROXIMATION_VALUE, false to move it outside of APPROXIMATION_VALUE
		*/
		virtual void moveAtBorder(vec3& point,bool inside) const = 0;

		/**
		* @brief Computes the normal for the point
		* @param point : the point from where the normal is computed
		* @return the normal vector
		* @since 1.02.00
		*/
		virtual vec3 computeNormal(const vec3& point) const = 0;

	protected :

		/** @brief Value used for approximation */
		static const float APPROXIMATION_VALUE;

		/**
		* @brief A helper static method to normalize a vec3
		*
		* If the vec3 is NULL, a random normal vec3 is set.<br>
		* The randomness is guaranteed to be uniformely distributed.
		*
		* @param v : the vec3 to normalize or randomize if not normalizable
		* @since 1.03.00
		*/
		static void normalizeOrRandomize(vec3& v);

		virtual void innerUpdateTransform();

	private :

		vec3 position;
		vec3 tPosition; // transformed position
	};


	inline void Zone::setPosition(const vec3& v)
	{
		position = tPosition = v;
		notifyForUpdate();
	}

	inline const vec3& Zone::getPosition() const
	{
		return position;
	}

	inline const vec3& Zone::getTransformedPosition() const
	{
		return tPosition;
	}

	inline void Zone::normalizeOrRandomize(vec3& v)
	{
//		while(!v.normalize())
		while(glm::length2(v) == 0.0)
		{
			do v = vec3(random(-1.0f,1.0f),random(-1.0f,1.0f),random(-1.0f,1.0f));
			while (glm::length2(v) > 1.0f);
		}
	}

	inline void Zone::innerUpdateTransform()
	{
		transformPos(tPosition,position);
	}
}

#endif
