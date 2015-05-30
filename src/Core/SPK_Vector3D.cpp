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


#include "Core/SPK_Vector3D.h"

namespace SPK
{
	float getSqrDist(const vec3& v0,const vec3& v1)
	{
		float dx = v0.x - v1.x;
		float dy = v0.y - v1.y;
		float dz = v0.z - v1.z;

		return dx * dx + dy * dy + dz * dz;
	}

	float getDist(const vec3& v0,const vec3& v1)
	{
		return std::sqrt(getSqrDist(v0,v1));
	}

	vec3 crossProduct(const vec3& v0,const vec3& v1)
	{
		vec3 result;

		result.x = v0.y * v1.z - v0.z * v1.y;
		result.y = v0.z * v1.x - v0.x * v1.z;
		result.z = v0.x * v1.y - v0.y * v1.x;

		return result;
	}

	void crossProduct(const vec3& v0,const vec3& v1,vec3& result)
	{
		result.x = v0.y * v1.z - v0.z * v1.y;
		result.y = v0.z * v1.x - v0.x * v1.z;
		result.z = v0.x * v1.y - v0.y * v1.x;
	}
}
