#pragma once
#include "common.h"
#include "Camera.h"

class Renderer
{
	using Color = glm::vec3;
private:
	int Windows_width;
	int Windows_height;
	uint32_t* mBuffer = nullptr;
	std::atomic<int> mCurrentPixel = 0;
public:
	int Windows_Massage();
	Renderer(int weight, int height);
	virtual ~Renderer() {};
	void Run(int width, int height);
	Camera mcamara;

private:
	Color RenderPixel(int x, int y) ;
	void RunRenderThread();


};

