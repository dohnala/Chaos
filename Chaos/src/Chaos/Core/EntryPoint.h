#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Application.h"

extern Chaos::Application* Chaos::CreateApplication();

int main(int argc, char** argv)
{
	Chaos::Log::Init();

	auto app = Chaos::CreateApplication();
	app->Run();
	delete app;
}