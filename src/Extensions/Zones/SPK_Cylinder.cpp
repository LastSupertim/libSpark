//////////////////////////////////////////////////////////////////////////////////
// SPARK particle engine														//
// Copyright (C) 2008-2010                                                      //
//  - Julien Fryer - julienfryer@gmail.com				                        //
//  - Thibault Lescoat -  info-tibo <at> orange <dot> fr						//
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

#include "Extensions/Zones/SPK_Cylinder.h"
#include "Core/SPK_Particle.h"

namespace SPK
{
	Cylinder::Cylinder(const vec3& position,const vec3& direction,float radius,float length) :
		Zone(position)
	{
		setDirection(direction);
		setRadius(radius);
		setLength(length);
	}

    bool Cylinder::contains(const vec3& v) const
    {
        float dist = dotProduct(tDirection,v - getTransformedPosition());

		vec3 ext = v - (tDirection*dist + getTransformedPosition());
//		float r = ext.getNorm();
		float r = glm::length(ext);

		return dist <= length*0.5f && dist >= -length*0.5f && r <= radius;
    }
    vec3 Cylinder::computeNormal(const vec3& point) const
    {
        float dist = dotProduct(tDirection,point - getTransformedPosition());
        if(dist >= length*0.5f) return tDirection;
		if(dist <= -length*0.5f) return -tDirection;

		vec3 ext = point - (tDirection*dist + getTransformedPosition());
//		float r = ext.getNorm(); ext = ext / r;
		float r = glm::length(ext); ext = ext / r;

		return ext;
    }

	void Cylinder::generatePosition(Particle& particle,bool full) const
	{
	    float cRadius = full ? random(0.0f,radius) : radius,
            cLength = full ? random(0.0f,length)-length*0.5f : length,
            cAngle = random(0.0f,3.15f); // 3.15 > PI, but it has no importance here...

	    // We need at least two points to compute a base
	    vec3 rPoint = getTransformedPosition() + vec3(10.0f,10.0f,10.0f);
	    float dist = dotProduct(tDirection,rPoint);
	    while(dist == 0.0f || tDirection*dist +getTransformedPosition() == rPoint)
	    {
	        // avoid dist == 0, which leads to a div by zero.
	        rPoint += vec3(10.0f,10.0f,random(-10.0f,10.0f));
	        dist = dotProduct(tDirection,rPoint);
	    }

	    vec3 p1 = tDirection*dist +getTransformedPosition();
	    dist = getDist(p1,rPoint);

	    vec3 a = (rPoint - p1) / dist;
//		vec3 tmp1 = tDirection, tmp2 = a; tmp2.crossProduct(tmp1*(-1));
		vec3 tmp1 = tDirection, tmp2 = a; glm::cross(tmp2, tmp1*(-1));
        vec3 b = tmp2;

        particle.position() = getTransformedPosition() + cLength * tDirection + a * cRadius * std::cos(cAngle) + b * cRadius * std::sin(cAngle);
	}

	bool Cylinder::intersects(const vec3& v0,const vec3& v1,vec3* intersection,vec3* normal) const
	{
	    if(!intersection) return false;

	    // mindist between line directed by tDir and line(v0 v1).
//	    vec3 u = v1 - v0; u.normalize();
		vec3 u = v1 - v0; u = glm::normalize(u);
	    if(tDirection == u || tDirection == -u) // colinear
	    {
	        float dist = dotProduct(tDirection,v0 - getTransformedPosition());

            vec3 ext = v0 - (tDirection*dist + getTransformedPosition());
//            float r = ext.getNorm(); ext = ext / r;
			float r = glm::length(ext); ext = ext / r;

            if(r == radius) //intersection
            {
                *intersection = getTransformedPosition() + ext * radius;
                if(normal)
                    *normal = computeNormal(*intersection);
                return true;
            }
            else if(r < radius)
            {
                *intersection = getTransformedPosition() + tDirection * length*0.5f + ext * r;
                if(normal)
                    *normal = computeNormal(*intersection);
                return true;
            }
            return false;
	    }
	    else
	    {
	        vec3 pp = getTransformedPosition() - v0, uv = u;
//	        uv.crossProduct(tDirection);
			uv = glm::cross(uv, tDirection);
//			float dist = std::abs(dotProduct(pp,uv))/uv.getNorm();
			float dist = std::abs(dotProduct(pp,uv))/glm::length(uv);

	        float d = dotProduct(tDirection,v0 - getTransformedPosition());
            vec3 ext = v0 - (tDirection*d + getTransformedPosition());
//            float r = ext.getNorm();
			float r = glm::length(ext);

	        float ah = std::cos(std::asin(dist/r))*r;
	        vec3 h = v0 + u*ah;

	        if(contains(h)) // intersection
	        {
	            float offset = 3.1415926535897932384626433832795f*0.5f*dist/radius;
	            *intersection = h - offset * u;
	            if(normal)
                    *normal = computeNormal(*intersection);
	            return true;
	        }
	        return false;
	    }
	}

	void Cylinder::moveAtBorder(vec3& v,bool inside) const
	{
	    float approx = inside ? -APPROXIMATION_VALUE : APPROXIMATION_VALUE;
        float dist = dotProduct(tDirection,v - getTransformedPosition());

		vec3 ext = v - (tDirection*dist + getTransformedPosition());
//		float r = ext.getNorm(); ext = ext / r;
		float r = glm::length(ext); ext = ext / r;
		if(dist > length*0.5f)
		{
		    v -= tDirection * (dist - length*0.5f - approx);
		    if(r > radius)
                v -= ext*(r-radius-approx);
            return;
		}
		else if(dist < -length * 0.5f)
		{
            v += tDirection * (length*0.5f - dist - approx);
            if(r > radius)
                v -= ext*(r-radius-approx);
            return;
        }

        if(r > radius)
            v -= ext*(r-radius-approx);
        else
            v += ext*(radius-r+approx);
	}

	void Cylinder::innerUpdateTransform()
	{
		Zone::innerUpdateTransform();
		transformDir(tDirection,direction);
//		tDirection.normalize();
		tDirection = glm::normalize(tDirection);
	}
}
