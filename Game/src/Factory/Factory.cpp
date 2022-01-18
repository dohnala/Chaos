#include "Factory/Factory.h"

#include "Color.h"
#include "ECS/Components/Components.h"

Chaos::Entity Factory::CreatePlayer(World& world)
{
	auto player = world.CreateEntity();
	player.AddComponent<PositionComponent>();
	player.AddComponent<KeybindingsComponent>();
	player.AddComponent<MoveComponent>(15.0f);
	player.AddComponent<CircleShieldComponent>(1.0f, Chaos::CircleProps::Create()
		.WithColorGradient(Color::Grey, Color::Black, 1.0f)
		.WithBorderDistortion(0.1f));
	player.AddComponent<CircleComponent>(0.6f, Chaos::CircleProps::Create()
		.WithColorGradient(Color::Blue, Color::Black, 1.5f)
		.WithBorderDistortion(0.3f));
	player.AddComponent<CircleColliderComponent>(1.0f);

	return player;
}

Chaos::Entity Factory::CreateCamera(World& world, Chaos::Entity player)
{
	auto camera = world.CreateEntity();
	camera.AddComponent<PositionComponent>();
	camera.AddComponent<CameraComponent>().Camera.SetOrthographicSize(30.0f);
	camera.AddComponent<FollowComponent>(player);

	return camera;
}

Chaos::Entity Factory::CreateCollectible(World& world)
{
	auto collectible = world.CreateEntity();
	collectible.AddComponent<PositionComponent>(world.GetRandomLocation());
	collectible.AddComponent<CollectibleComponent>();
	collectible.AddComponent<CircleColliderComponent>(0.4f);
	collectible.AddComponent<CircleComponent>(0.4f, Chaos::CircleProps::Create()
		.WithColorGradient(Color::Yellow, Color::Black, 1.5f)
		.WithBorderDistortion(0.3f));
	collectible.AddComponent<CircleGlowComponent>(0.8f, Chaos::CircleProps::Create()
		.WithColorGradient(Color::WithAlpha(Color::Yellow, 0.05f), Color::WithAlpha(Color::Yellow, 0.025f), 3.0f)
		.WithBorderDistortion(0.1f));
	collectible.AddComponent<DestroyEffectComponent>(10, Chaos::ParticleProps::Create()
		.WithDirectionVariance(glm::radians(360.0f))
		.WithSpeed(3.0f, 6.0f)
		.WithSize(0.1f, 0.05f)
		.WithColor(Color::Yellow)
		.WithAlpha(0.5f, 1.0f, 0.0f)
		.WithLifeTime(1.0f, 1.0f));

	return collectible;
}