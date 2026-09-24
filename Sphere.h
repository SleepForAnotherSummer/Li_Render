
#pragma once
#include "Ray.h"

struct Intersection
{
	glm::vec3 Position; //位置坐标
	glm::vec3 Normal;//法线坐标
	float t; //交点到射线原点的距离
};

class Sphere
{
public:
	Sphere(const glm::vec3& center, float radius);
	bool Intersect(Ray ray, Intersection& intersection) const;
private:
	float mRadius; 
	glm::mat4x4 mObjectToWorld;
	glm::mat4x4 mWorldToObject;

};

