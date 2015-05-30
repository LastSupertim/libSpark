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

#include "Extensions/Zones/SPK_Ring.h"
#include "Core/SPK_Particle.h"

namespace SPK
{
	Ring::Ring(const vec3& position,const vec3& normal,float minRadius,float maxRadius) :
		Zone(position)
	{
		setNormal(normal);
		setRadius(minRadius,maxRadius);
	}

	void Ring::setRadius(float minRadius,float maxRadius)
	{
		if (minRadius < 0.0f) minRadius = -minRadius;
		if (maxRadius < 0.0f) maxRadius = -maxRadius;
		if (minRadius > maxRadius) std::swap(minRadius,maxRadius);
		this->minRadius = minRadius;
		this->maxRadius = maxRadius;
		sqrMinRadius = minRadius * minRadius;
		sqrMaxRadius = maxRadius * maxRadius;
	}

	void Ring::generatePosition(Particle& particle,bool full) const
	{
		vec3 tmp;
		do tmp = vec3(random(-1.0f,1.0f),random(-1.0f,1.0f),random(-1.0f,1.0f));
//		while (tmp.getSqrNorm() > 1.0f);
		while (glm::length2(tmp) > 1.0f);

		crossProduct(tNormal,tmp,particle.position());
		normalizeOrRandomize(particle.position());

		particle.position() *= std::sqrt(random(sqrMinRadius,sqrMaxRadius)); // to have a uniform distribution
		particle.position() += getTransformedPosition();
	}

	bool Ring::intersects(const vec3& v0,const vec3& v1,vec3* intersection,vec3* normal) const
	{
		float dist0 = dotProduct(tNormal,v0 - getTransformedPosition());
		float dist1 = dotProduct(tNormal,v1 - getTransformedPosition());

		if ((dist0 <= 0.0f) == (dist1 <= 0.0f)) // both points are on the same side
			return false;

		if (dist0 <= 0.0f)
			dist0 = -dist0;
		else
			dist1 = -dist1;

		float ti = dist0 / (dist0 + dist1);

		vec3 vDir(v1 - v0);
//		float norm = vDir.getNorm();
		float norm = glm::length(vDir);

		norm *= ti;
		ti = norm < APPROXIMATION_VALUE ? 0.0f : ti * (norm - APPROXIMATION_VALUE) / norm;

		vDir *= ti;
		vec3 inter(v0 + vDir);

		float distFromCenter = getSqrDist(inter,getTransformedPosition());
		if (distFromCenter > sqrMaxRadius || distFromCenter < sqrMinRadius) // intersection is not in the ring
			return false;

		if (intersection != NULL)
		{
			*intersection = inter;
			if (normal != NULL)
				*normal = tNormal;
		}

		return true;
	}
	
	void Ring::moveAtBorder(vec3& v,bool inside) const
	{
		float dist = dotProduct(tNormal,v - getTransformedPosition());	
		v += tNormal * -dist;

		float distFromCenter = getSqrDist(v,getTransformedPosition());

		if (distFromCenter > sqrMaxRadius)
		{
			distFromCenter = std::sqrt(distFromCenter);
			vec3 vDir(v - getTransformedPosition());
			vDir *= maxRadius / distFromCenter;
			v = getTransformedPosition() + vDir;
		}
		else if (distFromCenter < sqrMinRadius)
		{
			distFromCenter = std::sqrt(distFromCenter);
			vec3 vDir(v - getTransformedPosition());
			vDir *= minRadius / distFromCenter;
			v = getTransformedPosition() + vDir;
		}
	}

	void Ring::innerUpdateTransform()
	{
		Zone::innerUpdateTransform();
		transformDir(tNormal,normal);
//		tNormal.normalize();
		tNormal = glm::normalize(tNormal);
	}
}
