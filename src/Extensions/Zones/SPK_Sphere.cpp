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


#include "Extensions/Zones/SPK_Sphere.h"
#include "Core/SPK_Particle.h"

namespace SPK
{
	Sphere::Sphere(const vec3& position,float radius) :
		Zone(position)
	{
		setRadius(radius);
	}

	void Sphere::generatePosition(Particle& particle,bool full) const
	{
		do particle.position() = vec3(random(-radius,radius),random(-radius,radius),random(-radius,radius));
//		while (particle.position().getSqrNorm() > radius * radius);
		while (glm::length2(particle.position()) > radius * radius);

		if ((!full)&&(radius > 0.0f))
//			particle.position() *= radius / particle.position().getNorm();
			particle.position() *= radius / glm::length(particle.position());

		particle.position() += getTransformedPosition();
	}

	bool Sphere::contains(const vec3& v) const
	{
		return getSqrDist(getTransformedPosition(),v) <= radius * radius;
	}

	bool Sphere::intersects(const vec3& v0,const vec3& v1,vec3* intersection,vec3* normal) const
	{
		float r2 = radius * radius;
		float dist0 = getSqrDist(getTransformedPosition(),v0);
		float dist1 = getSqrDist(getTransformedPosition(),v1);

		if ((dist0 <= r2) == (dist1 <= r2))
			return false;

		if (intersection != NULL)
		{
			vec3 vDir = v1 - v0;
//			float norm = vDir.getNorm();
			float norm = glm::length(vDir);

			float d = dotProduct(vDir,getTransformedPosition() - v0) / norm;
			float a = std::sqrt(r2 - dist0 + d * d);

			float ti;
			if (dist0 <= r2)
				ti = d - a;
			else
				ti = d + a;

			ti /= norm;

			if (ti < 0.0f) ti = 0.0f;
			if (ti > 1.0f) ti = 1.0f;

			norm *= ti;
			ti = norm < APPROXIMATION_VALUE ? 0.0f : ti * (norm - APPROXIMATION_VALUE) / norm;

			vDir *= ti;
			*intersection = v0 + vDir;

			if (normal != NULL)
			{
				if (dist0 <= r2)
					*normal = getTransformedPosition() - *intersection;
				else
					*normal = *intersection - getTransformedPosition();
//				normal->normalize();
				*normal = glm::normalize(*normal);
			}
		}

		return true;
	}

	void Sphere::moveAtBorder(vec3& v,bool inside) const
	{
		vec3 vDir = v - getTransformedPosition();
//		float norm = vDir.getNorm();
		float norm = glm::length(vDir);

		if (inside)
			vDir *= (radius + APPROXIMATION_VALUE) / norm;
		else
			vDir *= (radius - APPROXIMATION_VALUE) / norm;

		v = getTransformedPosition() + vDir;
	}

	vec3 Sphere::computeNormal(const vec3& point) const
	{
		vec3 normal(point - getTransformedPosition());
		normalizeOrRandomize(normal);
		return normal;
	}
}
