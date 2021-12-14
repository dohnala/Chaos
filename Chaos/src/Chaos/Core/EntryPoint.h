#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Application.h"

extern Chaos::Application* Chaos::CreateApplication();

int main()
{
	Chaos::Log::Init();
	CH_CORE_INFO("Chaos engine initialized");

	auto app = Chaos::CreateApplication();
	app->Run();
	delete app;
}