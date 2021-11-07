#pragma once
#include <vulkan/vulkan.h>
#define API_VERSION(major, minor) \
	((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12))

#define GET_API_VERSION_MAJOR(version) (((uint32_t)(version) >> 22) & 0x7FU)
#define GET_API_VERSION_MINOR(version) (((uint32_t)(version) >> 12) & 0x3FFU)

	enum RenderBackend
	{
		RENDER_BACKEND_GL,
		RENDER_BACKEND_VK,
	};

	enum RenderApiVersion
	{
		RENDER_API_NEWEST,
		RENDER_API_VK_1_2 = API_VERSION(1, 2),
		RENDER_API_VK_1_1 = API_VERSION(1, 1),
		RENDER_API_VK_1_0 = API_VERSION(1, 0),
		RENDER_API_GL_4_5 = API_VERSION(4, 5),
		RENDER_API_GL_4_3 = API_VERSION(4, 3),
	};

	struct RenderContextCreateInfo
	{
		RenderBackend backend = RENDER_BACKEND_VK;
		RenderApiVersion apiVersion = RenderApiVersion::RENDER_API_NEWEST;
#if defined(DEBUG)||defined(_DEBUG)|| defined(NDEBUG)
		bool useValidationLayer = true;
#else
		bool useValidationLayer = false;
#endif // defined(DEBUG)||defined(_DEBUG)|| defined(NDEBUG)
		bool useSurface = true;
		uint32_t swapChainBufferCount = 2;
		bool useVSync=false;
	};