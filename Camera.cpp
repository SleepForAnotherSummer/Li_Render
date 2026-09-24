#include "Camera.h"
#include "Ray.h"

void Camera::initialize(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up, float n, float f, float fov, int ScreenWidth, int ScreenHeight)
{
	
	glm::mat4x4 viewMatrix = glm::lookAtLH(position, target, up);
	glm::mat4x4 NDCMatrix = glm::perspectiveFovLH_ZO(fov, float(ScreenWidth), float(ScreenHeight), n, f);
	glm::mat4x4 viewportMatrix = glm::transpose(glm::mat4x4(
		ScreenWidth/2, 0, 0, 0,
		0, -(ScreenHeight/2), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		));//写错了，懒得改了，直接用转置
	glm::mat4x4 mCombinedMatrix = viewportMatrix * NDCMatrix * viewMatrix;
	glm::mat4x4 mInvCombinedMatrix = glm::inverse(mCombinedMatrix);
	CombinedMatrix = mCombinedMatrix;
	InvConbinedMatrix = mInvCombinedMatrix;


}

Ray Camera::getray(int x, int y) const //传入屏幕坐标
{
	Ray ray;
	ray.origin = position;
	glm::vec4 p = glm::vec4(x,y, 0.0f, 1.0f);
	glm::vec4 worldPosition = InvConbinedMatrix * p;
	worldPosition /= worldPosition.w; // 透视除法
	ray.direction = glm::normalize(worldPosition - glm::vec4(position, 1.0f));
	return ray;

	//遇到的几个问题，说一下，像是随笔，随便写写：
	//首先，传入的是屏幕坐标，绝对不鞥传入屏幕的宽和高，否则只是一个在屏幕右下角的固定的射线
	//其次，射线确定的是原点和方向，原点是摄像机位置，方向是从摄像机位置到屏幕坐标对应的世界坐标的向量
	//那么为了解决向量方式，在前面的Camera函数中返回了InvConbinedMatrix方法，这就是直接从NDC坐标转向世界坐标系
	//遗憾的是，NDC坐标系接下来针对屏幕坐标做了优化，所以，为了让屏幕坐标对应NDC坐标系，就需要将屏幕坐标矩阵NDC化，
	//才能够得到正确的世界坐标系位置，进而得到正确的射线方向
}
