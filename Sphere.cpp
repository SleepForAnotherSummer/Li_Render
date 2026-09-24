#pragma once
#include "common.h"
#include "Sphere.h"

Sphere::Sphere(const glm::vec3 & center, float radius)
	: mRadius(radius)
{
	mObjectToWorld = MakeWorldTranslation(center, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	mWorldToObject = glm::inverse(mObjectToWorld);
}

bool Sphere::Intersect(Ray ray, Intersection& intersection) const
{
	//世界空间转移到局部空间
	Ray r = mWorldToObject * ray;
	float a = glm::dot(r.direction, r.direction);
	float b = 2.0f * glm::dot(r.origin, r.direction);
	float c = glm::dot(r.origin, r.origin) - mRadius * mRadius;

	float delta = b * b - 4.0f * a * c;
	if (delta < 0.0f)
	{
		return false;
	}
	float sqrtDelta = sqrt(delta);
	float t1 = (-b - sqrtDelta) / (2.0f * a);
	float t2 = (-b + sqrtDelta) / (2.0f * a);
	
	//ti<t2 此处逻辑为，假设mint 和马maxt 为一个数轴上的两个点，从t1到t2单独在数轴上比较，此处代码逻辑非常复杂，建议使用数轴理解

	if (t2 < r.RayMin)
		return false;
	if(t1 < r.RayMin && t2 > r.RayMin && t2 < r.RayMax)
	{
		float t = t2;
		return true;
	}
	
	if(t1 > r.RayMin&& t2 < r.RayMax)
	{
		float t = t1;
		return true;
	}
	if (t1 > r.RayMin && t1 < r.RayMax && t2 > r.RayMin )
	{
		float t = t1;
		return true;
	}
	if(t1 > r.RayMax)
		return false;
	
}
	 