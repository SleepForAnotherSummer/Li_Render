#include "Renderer.h"

Renderer::Renderer(int width, int height)
	: Windows_width(width), Windows_height(height)
{
	mCurrentPixel = 0;
	Camera mycamera;
	
	mycamera.initialize(
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 0.1f, 1.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		20.0f, 30.0f, 10.0f, 600, 800);

	
}

void Renderer::Run(int width, int height)
{
	//基础渲染工作，32位像素点
	width = Windows_width;
	height = Windows_height;
	struct mfb_window* window = mfb_open_ex("3D Renderer", width, height, MFB_WF_RESIZABLE);
	if (window == NULL)
		return;
	mBuffer = (uint32_t*)malloc(Windows_width * Windows_height * 4);

	//渲染方法
	std::thread renderThread(&Renderer::RunRenderThread,this);
	renderThread.detach();


	//获取CPU核心数,使用少一个核心，因为主线程也在运行
	int CPU_number = std::thread::hardware_concurrency();
	
	for (int i=1; i < CPU_number;i++)
	{
		std::vector<std::thread>renderThreads(CPU_number);
		std::thread renderThread(&Renderer::RunRenderThread, this);
		renderThread.detach();
	}

	

	//保证连续运行
	mfb_update_state state;
	do
	{
		state = mfb_update_ex(window, mBuffer, width, height);

		if (state != MFB_STATE_OK)
			break;
	} while (mfb_wait_sync(window));

	free(mBuffer);
	mBuffer = NULL;
	window = NULL;
}



Color Renderer::RenderPixel(int x, int y)
{
	Color color;
	color.r = float(x) / Windows_width;
	color.g = float(y) / Windows_height;
	color.b = 0.7f;
	return color;
}

//渲染线程入口函数
void Renderer::RunRenderThread()
{
	//投影到屏幕
	int width = Renderer::Windows_width;
	int height = Renderer::Windows_height;
	while (true)
	{
		int pixelIndex = mCurrentPixel.fetch_add(1);
		//获取下一个像素点
		if(pixelIndex >= width * height)
		{
			break;
		}
		int x = pixelIndex % width;
		int y = pixelIndex / width;
		Color color = RenderPixel(x, y);
		uint32_t r = glm::clamp((uint32_t)std::round(color.r * 255.0f), 0u, 255u);
		uint32_t g = glm::clamp((uint32_t)std::round(color.g * 255.0f), 0u, 255u);
		uint32_t b = glm::clamp((uint32_t)std::round(color.b * 255.0f), 0u, 255u);
	}
}
//uint32_t r = glm::clamp((uint32_t)std::round(color.r * 255.0f), 0u, 255u);

int Renderer::Windows_Massage() {
	std::cout << "Please enter your ScreenWidth" << std::endl;
	std::cin >> Windows_width;
	std::cout << "Plwase enter your ScreenHeight" << std::endl;
	std::cin >> Windows_height;
	return Windows_width;
	return Windows_height;
}