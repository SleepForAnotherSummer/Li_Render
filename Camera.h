#pragma once
#include "common.h"
#include "Ray.h"
class Camera
{
public:
	void initialize(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, float n, float f, 
		float fov,int ScreenWidth, int ScreenHeight);

	Ray getray(int x, int y) const;
	
private:
	glm::vec3 position;
	glm::mat4x4 CombinedMatrix;
	glm::mat4x4 InvConbinedMatrix;
	glm::vec4 RayOrigin;


};

