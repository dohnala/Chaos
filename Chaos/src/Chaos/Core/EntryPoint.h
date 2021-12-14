#pragma once

#include "Chaos/Core/Log.h"

extern Chaos::Application* Chaos::CreateApplication();

int main()
{
	Chaos::Log::Init();
	CH_ENGINE_INFO("Chaos engine initialized");

	auto app = Chaos::CreateApplication();
	app->Run();
	delete app;
}