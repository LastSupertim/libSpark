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


#ifndef H_SPK_VECTOR3D
#define H_SPK_VECTOR3D

#include "Core/SPK_DEF.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
using glm::vec3;

namespace SPK
{
	////////////////////////
	// External operators //
	////////////////////////

	/**
	* @brief Adds two vec3
	*
	* This function performs these operations :<br><i>
	* result.x = v0.x + v1.x<br>
	* result.y = v0.y + v1.y<br>
	* result.z = v0.z + v1.z</i>
	*
	* @param v0 : the first vector3D
	* @param v1 : the second vector3D
	* @return the result vector3D
	*/
	vec3 operator+(const vec3& v0,const vec3& v1);

	/**
	* @brief Substracts two vec3
	*
	* This function performs these operations :<br><i>
	* result.x = v0.x - v1.x<br>
	* result.y = v0.y - v1.y<br>
	* result.z = v0.z - v1.z</i>
	*
	* @param v0 : the first vector3D
	* @param v1 : the second vector3D
	* @return the result vector3D
	*/
	vec3 operator-(const vec3& v0,const vec3& v1);

	/**
	* @brief Adds a vec3 and a float
	*
	* This function performs these operations :<br><i>
	* result.x = v.x + f<br>
	* result.y = v.y + f<br>
	* result.z = v.z + f</i>
	*
	* @param v : the vector3D
	* @param f : the floating number
	* @return the result vector3D
	*/
	vec3 operator+(const vec3& v,float f);

	/**
	* @brief Adds a float and a vec3
	*
	* This function performs these operations :<br><i>
	* result.x = f + v.x<br>
	* result.y = f + v.y<br>
	* result.z = f + v.z</i>
	*
	* @param f : the floating number
	* @param v : the vector3D
	* @return the result vector3D
	*/
	vec3 operator+(float f,const vec3& v);

	/**
	* @brief Substracts a float to a vec3
	*
	* This function performs these operations :<br><i>
	* result.x = v.x - f<br>
	* result.y = v.y - f<br>
	* result.z = v.z - f</i>
	*
	* @param v : the vector3D
	* @param f : the floating number
	* @return the result vector3D
	*/
	vec3 operator-(const vec3& v,float f);

	/**
	* @brief Substracts a vec3 to a float
	*
	* This function performs these operations :<br><i>
	* result.x = f - v.x<br>
	* result.y = f - v.y<br>
	* result.z = f - v.z</i>
	*
	* @param f : the floating number
	* @param v : the vector3D
	* @return the result vector3D
	*/
	vec3 operator-(float f,const vec3& v);

	/**
	* @brief Multiplies a vec3 by a float
	*
	* This function performs these operations :<br><i>
	* result.x = v.x * f<br>
	* result.y = v.y * f<br>
	* result.z = v.z * f</i>
	*
	* @param v : the vector3D
	* @param f : the floating number
	* @return the result vector3D
	*/
	vec3 operator*(const vec3& v,float f);

	/**
	* @brief Multiplies a float by a vec3
	*
	* This function performs these operations :<br><i>
	* result.x = f * v.x<br>
	* result.y = f * v.y<br>
	* result.z = f * v.z</i>
	*
	* @param f : the floating number
	* @param v : the vector3D
	* @return the result vector3D
	*/
	vec3 operator*(float f,const vec3& v);

	/**
	* @brief Divides a vec3 by a float
	*
	* This function performs these operations :<br><i>
	* result.x = v.x / f<br>
	* result.y = v.y / f<br>
	* result.z = v.z / f</i>
	*
	* @param v : the vector3D
	* @param f : the floating number
	* @return the result vector3D
	*/
	vec3 operator/(const vec3& v,float f);

	/**
	* @brief Divides a float by a vec3
	*
	* This function performs these operations :<br><i>
	* result.x = f / v.x<br>
	* result.y = f / v.y<br>
	* result.z = f / v.z</i>
	*
	* @param f : the floating number
	* @param v : the vector3D
	* @return the result vector3D
	*/
	vec3 operator/(float f,const vec3& v);

	/**
	* @brief Tests whether 2 vec3 are equal
	* @param v0 : the first vec3 to compare
	* @param v1 : the second vec3 to compare
	* @return true if the vec3 are equal, false if not
	* @since 1.01.01
	*/
	bool operator==(const vec3& v0,const vec3& v1);

	/**
	* @brief Tests whether 2 vec3 are different
	* @param v0 : the first vec3 to compare
	* @param v1 : the second vec3 to compare
	* @return true if the vec3 are different, false if not
	* @since 1.01.01
	*/
	bool operator!=(const vec3& v0,const vec3& v1);

	/**
	* @brief Writes a vec3 on an output stream
	*
	* The vec3 is written that way : <i>(x,y,z)</i>
	*
	* @param s : the output stream where to write
	* @param v : the vec3 to write to the output stream
	* @return the output stream
	* @since 1.01.01
	*/
	std::ostream& operator<<(std::ostream& s,const vec3& v);

	////////////////////////
	// External functions //
	////////////////////////

	/**
	* @brief Returns the square distance between two vec3
	*
	* This method is faster than getDist(const vec3&,const vec3&) and should be used when possible.
	*
	* @param v0 : the first vec3
	* @param v1 : the second vec3
	* @return the square distance between the two vec3
	*/
	extern SPK_PREFIX float getSqrDist(const vec3& v0,const vec3& v1);

	/**
	* @brief Returns the distance between two vec3
	* @param v0 : the first vec3
	* @param v1 : the second vec3
	* @return the distance between the two vec3
	*/
	extern SPK_PREFIX float getDist(const vec3& v0,const vec3& v1);

	/**
	* @brief Returns the dot product between two vec3
	* @param v0 : the first vec3
	* @param v1 : the second vec3
	* @return the dot product (v0 . v1)
	*/
	float dotProduct(const vec3& v0,const vec3& v1);

	/**
	* @brief Returns the cross product between two vec3
	* @param v0 : the first vec3
	* @param v1 : the second vec3
	* @return the cross product (v0 x v1)
	*/
	extern SPK_PREFIX vec3 crossProduct(const vec3& v0,const vec3& v1);

	/**
	* @brief Computes the cross product between two vec3 and stores the result in the vec3 result
	* @param v0 : the first vec3
	* @param v1 : the second vec3
	* @param result : the vec3 where to store the cross product (v0 x v1)
	*/
	extern SPK_PREFIX void crossProduct(const vec3& v0,const vec3& v1,vec3& result);


	inline float dotProduct(const vec3& v0,const vec3& v1)
	{
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}

	inline vec3 operator+(const vec3& v0,const vec3& v1)
	{
		return vec3(v0.x + v1.x,v0.y + v1.y,v0.z + v1.z);
	}

	inline vec3 operator-(const vec3& v0,const vec3& v1)
	{
		return vec3(v0.x - v1.x,v0.y - v1.y,v0.z - v1.z);
	}

	inline vec3 operator+(const vec3& v,float f)
	{
		return vec3(v.x + f,v.y + f,v.z + f);
	}

	inline vec3 operator+(float f,const vec3& v)
	{
		return vec3(v.x + f,v.y + f,v.z + f);
	}

	inline vec3 operator-(const vec3& v,float f)
	{
		return vec3(v.x - f,v.y - f,v.z - f);
	}

	inline vec3 operator-(float f,const vec3& v)
	{
		return vec3(v.x - f,v.y - f,v.z - f);
	}

	inline vec3 operator*(const vec3& v,float f)
	{
		return vec3(v.x * f,v.y * f,v.z * f);
	}

	inline vec3 operator*(float f,const vec3& v)
	{
		return vec3(v.x * f,v.y * f,v.z * f);
	}

	inline vec3 operator/(const vec3& v,float f)
	{
		float mul = 1.0f / f;
		return vec3(v.x * mul,v.y * mul,v.z * mul);
	}

	inline vec3 operator/(float f,const vec3& v)
	{
		return vec3(f / v.x,f / v.y,f / v.z);
	}

	inline bool operator==(const vec3& v0,const vec3& v1)
	{
		return (v0.x == v1.x)&&(v0.y == v1.y)&&(v0.z == v1.z);
	}

	inline bool operator!=(const vec3& v0,const vec3& v1)
	{
		return (v0.x != v1.x)||(v0.y != v1.y)||(v0.z != v1.z);
	}

	inline std::ostream& operator<<(std::ostream& s,const vec3& v)
	{
		return s << '(' << v.x << ',' << v.y << ',' << v.z << ')';
	}
}

#endif
