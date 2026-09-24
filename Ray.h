#include "common.h"  // 或根据实际位置使用正确相对/绝对路径，例如 "../include/common.h"
struct Ray
{
	glm::vec3 origin;
	glm::vec4 direction;
	
	float RayMin = 0.0f;
	float RayMax = FLT_MAX;
};

inline Ray operator* (const glm::mat4x4& m, const Ray& ray)
{
	Ray result;
	result.origin = glm::vec3(m * glm::vec4(ray.origin, 1.0f));
	result.direction = glm::normalize(m * ray.direction);
	result.RayMin = ray.RayMin;
	result.RayMax = ray.RayMax;
	return result;

}