#pragma once

#include "Chaos.h"

#include "Player.h"

class Map
{
public:
	void Init();

	void OnUpdate(Chaos::Timestep ts);
	void OnRender();
private:
	Player m_Player;
};