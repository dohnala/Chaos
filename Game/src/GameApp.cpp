#include "Chaos.h"
#include "Chaos/Core/EntryPoint.h"

#include "GameLayer.h"
#include "Debug/CircleRendererDebugLayer.h"

class GameApp : public Chaos::Application
{
public:
	GameApp()
		: Application("Game App", 1280, 720)
	{
		PushLayer(new GameLayer());
		//PushLayer(new CircleRendererDebugLayer());
	}

	~GameApp()
	{}
};

Chaos::Application* Chaos::CreateApplication()
{
	return new GameApp();
}