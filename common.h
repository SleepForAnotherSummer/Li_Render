#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <MiniFB.h>
#include <thread>
#include <vector>
#include <atomic>
#include <glm/ext.hpp>
using Color = glm::vec3;



//下面函数是答应向量和矩阵的函数
void print_vec3(glm::vec3 v)
{
	std::cout << "Vector: (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}
void print_mat4x4(glm::mat4x4 m)
{
	std::cout << "Matrix: " << std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

//下面函数是基础的数学方法
glm::vec3 initEuler(glm::vec3 oler)//初始化欧拉角，将欧拉角从度数转换为弧度
{
	const float PI = glm::pi<float>();
	return glm::vec3(oler.x / 180 * PI, oler.y / 180 * PI, oler.z / 180 * PI);
}
//下面是另外一种方法去实现欧拉角的初始化，使用glm库自带的函数
//glm::roadions()——此函数可以将输入的数字转换为弧度，返回一个旋转矩阵

//下面函数是图形的基础操作，包括平移旋转和缩放
glm::mat4x4 MakeTranslation(glm::vec3 t)
{
	return glm::mat4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		t.x, t.y, t.z, 1.0f
	);
}

glm::mat4x4 MakeRotation(glm::vec3 oler)//使用欧拉角来进行传入工作
{
	float cosx = cosf(oler.x);
	float sinx = sinf(oler.x);
	float cosy = cosf(oler.y);
	float siny = sinf(oler.y);
	float cosz = cosf(oler.z);
	float sinz = sinf(oler.z);
	glm::mat4x4 RotationX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosx, -sinx, 0.0f,
		0.0f, sinx, cosx, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	glm::mat4x4 RotationY(
		cosy, 0.0f, -siny, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		siny, 0.0f, cosy, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	glm::mat4x4 RotationZ(
		cosz, sinz, 0.0f, 0.0f,
		-sinz, cosz, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	return RotationZ * RotationY * RotationX;//注意矩阵的乘法顺序，先旋转X轴，再旋转Y轴，最后旋转Z轴，在此处是Z*Y*X的顺序

}

glm::mat4x4 MakeScale(glm::vec3 s, float a)
{
	const float EPSILON = 1e-6f;
	if ((s.x - 1.0f) < EPSILON && (s.y - 1.0f) < EPSILON && (s.z - 1.0f) < EPSILON)
	{
		std::cout << "Warning: 您必须更改缩放比例" << std::endl;
		std::exit(0);
	}
	if ((s.x - 0.0f) < EPSILON || (s.y - 0.0f) < EPSILON || (s.z - 0.0f) < EPSILON)
	{
		std::cout << "Warning: 缩放比例不能为0" << std::endl;
		std::exit(0);
	}
	if (a != 1.0 && a != 0.0f)
	{
		std::cout << "Warning:  齐次化坐标只允许1.0f或0.0f。" << std::endl;
		std::exit(0);
	}
	return glm::mat4x4(
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, a
	);
}

inline glm::mat4x4 MakeWorldTranslation(glm::vec3 newCenter, glm::vec3 oler, float s)
{
	glm::mat4x4 translationMatrix = MakeTranslation(newCenter);
	glm::mat4x4 rotationMatrix = MakeRotation(oler);
	glm::mat4x4 scaleMatrix = MakeScale(glm::vec3(s, s, s), 1.0f);
	return translationMatrix * rotationMatrix * scaleMatrix;
}