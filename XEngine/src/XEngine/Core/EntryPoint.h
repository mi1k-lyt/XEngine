#pragma once

#ifdef XENGINE_PLATFORM_WINDOWS

extern XEngine::Application* XEngine::CreateApplication();
	
int main(int argc, char** argv)
{
	XEngine::Log::Init();
	XENGINE_CORE_WARN("Init Log");

	int a = 3;
	XENGINE_INFO("hello {0}", a);

	auto demo = XEngine::CreateApplication();
	demo->Run();
	delete demo;

	return 0;
}

#endif
