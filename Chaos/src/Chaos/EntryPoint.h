#pragma once

extern Chaos::Application* Chaos::CreateApplication();

int main()
{
	auto app = Chaos::CreateApplication();
	app->Run();
	delete app;
}