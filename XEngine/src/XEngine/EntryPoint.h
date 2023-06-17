#pragma once

#ifdef XE_PLATFORM_WINDOWS

extern XEngine::Application* XEngine::CreateApplication();
	
int main(int argc, char** argv)
{
	
	auto demo = XEngine::CreateApplication();
	demo->Run();
	delete demo;

	return 0;
}

#endif
