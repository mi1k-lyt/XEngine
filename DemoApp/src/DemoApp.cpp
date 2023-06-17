#include <XEngine.h>

class Demo : public XEngine::Application
{
public:
	Demo()
	{
	
	}

	~Demo()
	{
	
	}
};

XEngine::Application* XEngine::CreateApplication()
{
	return new Demo();
}
