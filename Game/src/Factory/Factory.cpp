#include "Factory/Factory.h"

#include "Color.h"

Chaos::Entity Factory::CreatePlayer(World& world)
{
	auto player = world.CreateEntity();
	
	player.AddComponent<PositionComponent>();
	player.AddComponent<InputComponent>();
	player.AddComponent<AimComponent>();
	player.AddComponent<MoveComponent>(75.0f, 15.0f, 3.0f);
	player.AddComponent<CircleColliderComponent>(0.6f, Layer::Player, Layer::Enemy | Layer::Collectible);
	player.AddComponent<CollectibleFollowComponent>(3.0f, 0.0f, 0.75f);
	
	player.AddComponent<CircleComponent>(0.6f, Chaos::CircleProps::Create()
		.WithColor(Color::Blue));
	player.AddComponent<AimIndicatorComponent>(0.75f, 0.3f, Chaos::PolygonProps::Create()
		.WithVertexCount(3)
		.WithColor(Color::Blue));
	player.AddComponent<CircleGlowComponent>(1.0f, Chaos::CircleProps::Create()
		.WithColor(Color::WithAlpha(Color::Blue, 0.05f)));

	player.AddComponent<TrailEffectComponent>(glm::vec2(0.0f), VFX::TrailEffect::Create()
		.WithParticleCount(3.0f)
		.WithParticle(Chaos::ParticleProps::Create()
			.WithPositionVariance(0.3f)
			.WithSize(0.1f, 0.05f)
			.WithColor(Color::Blue)
			.WithAlpha(0.75f, 0.5f, 0.0f)
			.WithLifeTime(0.25f, 0.5f)));
		

	player.AddComponent<ImpactEffectComponent>(5, Chaos::ParticleProps::Create()
		.WithDirectionVariance(glm::radians(90.0f))
		.WithSpeed(2.0f, 4.0f)
		.WithSize(0.1f, 0.05f)
		.WithColor(Color::Blue)
		.WithAlpha(0.5f, 1.0f, 0.0f)
		.WithLifeTime(1.0f, 1.0f));
	
	auto& skills = player.AddComponent<SkillSlotsComponent>();
	skills.SkillSlot1 = CreateSkill(world, SkillID::ArcaneShot, player);

	return player;
}

Chaos::Entity Factory::CreateCamera(World& world, Chaos::Entity player)
{
	auto camera = world.CreateEntity();
	
	camera.AddComponent<PositionComponent>();
	camera.AddComponent<CameraComponent>().Camera.SetOrthographicSize(30.0f);
	camera.AddComponent<FollowComponent>(player, 1.0f);

	return camera;
}

Chaos::Entity Factory::CreateCollectible(World& world)
{
	auto collectible = world.CreateEntity();
	
	collectible.AddComponent<PositionComponent>(world.GetRandomLocation());
	collectible.AddComponent<CollectibleComponent>();
	collectible.AddComponent<CircleColliderComponent>(0.2f, Layer::Collectible, Layer::Player);
	
	collectible.AddComponent<CircleComponent>(0.2f, Chaos::CircleProps::Create()
		.WithColor(Color::Yellow));
	collectible.AddComponent<CircleGlowComponent>(0.4f, Chaos::CircleProps::Create()
		.WithColor(Color::WithAlpha(Color::Yellow, 0.05f)));
	
	collectible.AddComponent<DestroyEffectComponent>(10, Chaos::ParticleProps::Create()
		.WithDirectionVariance(glm::radians(360.0f))
		.WithSpeed(3.0f, 6.0f)
		.WithSize(0.1f, 0.05f)
		.WithColor(Color::Yellow)
		.WithAlpha(0.5f, 1.0f, 0.0f)
		.WithLifeTime(1.0f, 1.0f));

	return collectible;
}

Chaos::Entity Factory::CreateEnemy(World& world)
{
	auto enemy = world.CreateEntity();
	
	enemy.AddComponent<PositionComponent>(world.GetRandomLocation());
	enemy.AddComponent<CircleColliderComponent>(0.4f, Layer::Enemy, Layer::Player | Layer::Projectile);
	
	enemy.AddComponent<CircleGlowComponent>(0.7f, Chaos::CircleProps::Create()
		.WithColor(Color::WithAlpha(Color::Red, 0.05f)));
	enemy.AddComponent<CircleComponent>(0.4f, Chaos::CircleProps::Create()
		.WithColor(Color::Red));
	
	enemy.AddComponent<ImpactEffectComponent>(5, Chaos::ParticleProps::Create()
		.WithDirectionVariance(glm::radians(90.0f))
		.WithSpeed(2.0f, 4.0f)
		.WithSize(0.1f, 0.05f)
		.WithColor(Color::Red)
		.WithAlpha(0.5f, 1.0f, 0.0f)
		.WithLifeTime(1.0f, 1.0f));

	return enemy;
}

Chaos::Entity Factory::CreateSkill(World& world, SkillID skill, Chaos::Entity owner)
{
	if (skill == SkillID::Fireball)
	{
		auto fireball = world.CreateEntity();

		fireball.AddComponent<SkillComponent>(skill, owner, 0.5f);
		
		auto& projectile = fireball.AddComponent<ProjectileSkillComponent>(0.2f, 45.0f);
		
		projectile.ProjectileProps = Chaos::CircleProps::Create()
			.WithColor(Color::Yellow);
		
		projectile.TrailEffect = VFX::TrailEffect::Create()
			.WithParticleCount(6.0f)
			.WithParticle(Chaos::ParticleProps::Create()
				.WithPositionVariance(0.1f)
				.WithDirectionVariance(glm::radians(90.0f))
				.WithSpeed(0.25f, 0.5f)
				.WithSize(0.1f, 0.05f)
				.WithColorGradient(Color::Yellow, Color::Red)
				.WithAlpha(0.75f, 0.5f, 0.0f)
				.WithLifeTime(0.25f, 0.5f));

		return fireball;
	}

	if (skill == SkillID::PoisonBolt)
	{
		auto poisonBolt = world.CreateEntity();
		
		poisonBolt.AddComponent<SkillComponent>(skill, owner, 0.5f);
		
		auto& projectile = poisonBolt.AddComponent<ProjectileSkillComponent>(0.2f, 45.0f);
		
		projectile.ProjectileProps = Chaos::CircleProps::Create()
			.WithColor(Color::Green);

		projectile.TrailEffect = VFX::TrailEffect::Create()
			.WithParticleCount(6.0f)
			.WithParticle(Chaos::ParticleProps::Create()
				.WithPositionVariance(0.1f)
				.WithDirectionVariance(glm::radians(90.0f))
				.WithSpeed(0.25f, 0.5f)
				.WithSize(0.1f, 0.05f)
				.WithColorGradient(Color::Yellow, Color::Green)
				.WithAlpha(0.75f, 0.5f, 0.0f)
				.WithLifeTime(0.25f, 0.5f));
		
		projectile.DestroyEffect = Chaos::ParticleProps::Create()
			.WithDirectionVariance(glm::radians(90.0f))
			.WithSpeed(2.0f, 4.0f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::Yellow, Color::Green)
			.WithAlpha(0.5f, 1.0f, 0.0f)
			.WithLifeTime(1.0f, 1.0f);
		projectile.DestroyEffectCount = 10;

		return poisonBolt;
	}

	if (skill == SkillID::ArcaneShot)
	{
		auto arcaneShot = world.CreateEntity();
		
		arcaneShot.AddComponent<SkillComponent>(skill, owner, 0.25f);
		
		auto& projectile = arcaneShot.AddComponent<ProjectileSkillComponent>(0.15f, 45.0f);
		
		projectile.ProjectileProps = Chaos::CircleProps::Create()
			.WithColor(Color::Pink);
		
		projectile.TrailEffect = VFX::TrailEffect::Create()
			.WithParticleCount(6.0f)
			.WithDirectionType(VFX::TrailEffect::DirectionType::Sin)
			.WithParticle(Chaos::ParticleProps::Create()
				.WithPositionVariance(0.1f)
				.WithDirectionVariance(glm::radians(0.0f))
				.WithSpeed(3.0f, 3.0f)
				.WithSize(0.1f, 0.05f)
				.WithColorGradient(Color::White, Color::Pink)
				.WithAlpha(0.75f, 0.5f, 0.0f)
				.WithLifeTime(0.25f, 0.5f));

		projectile.DestroyEffect = Chaos::ParticleProps::Create()
			.WithDirectionVariance(glm::radians(90.0f))
			.WithSpeed(2.0f, 4.0f)
			.WithSize(0.1f, 0.05f)
			.WithColorGradient(Color::White, Color::Pink)
			.WithAlpha(0.5f, 1.0f, 0.0f)
			.WithLifeTime(1.0f, 1.0f);
		projectile.DestroyEffectCount = 10;

		return arcaneShot;
	}

	CH_ASSERT(false, "Unknown Skill!");
	return Chaos::Entity::Null;
}