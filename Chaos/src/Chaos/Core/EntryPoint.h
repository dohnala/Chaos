#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Application.h"

extern Chaos::Application* Chaos::CreateApplication();

int main()
{
	Chaos::Log::Init();

	auto app = Chaos::CreateApplication();
	app->Run();
	delete app;
}