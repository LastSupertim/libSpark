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


#ifndef H_SPK_PLANE
#define H_SPK_PLANE

#include "Core/SPK_Zone.h"
#include "Core/SPK_Particle.h"

namespace SPK
{
	/**
	* @class Plane
	* @brief A Zone defining a plane in the universe
	*
	* A Plane is defined by 2 parameters :
	* <ul>
	* <li>A Position is the universe</li>
	* <li>A Normal</li>
	* </ul>
	* The defined Plane is the Plane having the normal and passing by the position.<br>
	* The direction of the normal defines the sens of the plane. The normal goes from inside the Plane to outside.<br>
	* <br>
	* Note that the normal does not have to be normalized as it is normalized internally when set.
	*/
	class SPK_PREFIX Plane : public Zone
	{
		SPK_IMPLEMENT_REGISTERABLE(Plane)

	public :

		//////////////////
		// Constructors //
		//////////////////

		/**
		* @brief Constructor of Plane
		* @param position : the position of the Plane
		* @param normal : the normal of the Plane
		*/
		Plane(const vec3& position = vec3(0.0f,0.0f,0.0f),const vec3& normal = vec3(0.0f,1.0f,0.0f));

		/**
		* @brief Creates and registers a new Plane
		* @param position : the position of the Plane
		* @param normal : the normal of the Plane
		* @return a new registered plane
		* @since 1.04.00
		*/
		static Plane* create(const vec3& position = vec3(0.0f,0.0f,0.0f),const vec3& normal = vec3(0.0f,1.0f,0.0f));

		/////////////
		// Setters //
		/////////////

		/**
		* @brief Sets the normal of this Plane
		*
		* Note that the normal is normalized internally.
		*
		* @param normal :  the normal of this Plane
		*/
		void setNormal(const vec3& normal);

		/////////////
		// Getters //
		/////////////

		/**
		* @brief Gets the normal of this Plane
		* @return the normal of this Plane
		*/
		const vec3& getNormal() const;

		/**
		* @brief Gets the transformed normal of this Plane
		* @return the transformed normal of this Plane
		* @since 1.05.00
		*/
		const vec3& getTransformedNormal() const;

		///////////////
		// Interface //
		///////////////

		virtual void generatePosition(Particle& particle,bool full) const;
		virtual bool contains(const vec3& v) const;
		virtual bool intersects(const vec3& v0,const vec3& v1,vec3* intersection,vec3* normal) const;
		virtual void moveAtBorder(vec3& v,bool inside) const;
		virtual vec3 computeNormal(const vec3& point) const;

	protected :

		virtual void innerUpdateTransform();

	private :

		vec3 normal;
		vec3 tNormal;
	};


	inline Plane* Plane::create(const vec3& position,const vec3& normal)
	{
		Plane* obj = new Plane(position,normal);
		registerObject(obj);
		return obj;
	}
		
	inline void Plane::setNormal(const vec3& normal)
	{
		this->normal = glm::normalize(normal);
//		this->normal.normalize();
		tNormal = this->normal;
		notifyForUpdate();
	}

	inline const vec3& Plane::getNormal() const
	{
		return normal;
	}

	inline const vec3& Plane::getTransformedNormal() const
	{
		return tNormal;
	}

	inline void Plane::generatePosition(Particle& particle,bool full) const
	{
		particle.position() = getTransformedPosition();
	}

	inline bool Plane::contains(const vec3& v) const
	{
		return dotProduct(normal,v - getTransformedPosition()) <= 0.0f;
	}

	inline vec3 Plane::computeNormal(const vec3& point) const
	{
		return tNormal;
	}
}

#endif
