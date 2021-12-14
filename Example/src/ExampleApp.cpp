#include <Chaos.h>

class ExampleApp : public Chaos::Application
{
public:
	ExampleApp()
		: Application("Example App")
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