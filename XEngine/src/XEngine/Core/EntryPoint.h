#pragma once

#include "XEngine/Core/Core.h"
#include "XEngine/Core/Application.h"

#ifdef XENGINE_PLATFORM_WINDOWS

extern XEngine::Application* XEngine::CreateApplication();
	
int main(int argc, char** argv)
{
	XEngine::Log::Init();
	XENGINE_CORE_WARN("Init Log");

	auto app = XEngine::CreateApplication();
	app->Run();
	delete app;

}

#endif
