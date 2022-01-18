#include "Chaos.h"
#include "Chaos/Core/EntryPoint.h"

#include "GameLayer.h"

class GameApp : public Chaos::Application
{
public:
	GameApp()
		: Application("Game App", 1280, 720)
	{
		PushLayer(new GameLayer());
	}

	~GameApp()
	{}
};

Chaos::Application* Chaos::CreateApplication()
{
	return new GameApp();
}