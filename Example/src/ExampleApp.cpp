#include <Chaos.h>

class ExampleApp : public Chaos::Application
{
public:
	ExampleApp()
	{
		CH_INFO("ExampleApp started");
	}

	~ExampleApp()
	{
	}
};

Chaos::Application* Chaos::CreateApplication()
{
	return new ExampleApp();
}