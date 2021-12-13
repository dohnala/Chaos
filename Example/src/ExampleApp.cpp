#include <Chaos.h>

class ExampleApp : public Chaos::Application
{
public:
	ExampleApp()
	{
		Chaos::Log("ExampleApp started");
	}

	~ExampleApp()
	{
	}
};

Chaos::Application* Chaos::CreateApplication()
{
	return new ExampleApp();
}