#pragma once

#ifdef XE_PLATFORM_WINDOWS

extern XEngine::Application* XEngine::CreateApplication();
	
int main(int argc, char** argv)
{
	XEngine::Log::Init();
	XE_CORE_WARN("Init Log");

	int a = 3;
	XE_INFO("hello {0}", a);

	auto demo = XEngine::CreateApplication();
	demo->Run();
	delete demo;

	return 0;
}

#endif
