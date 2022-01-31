#include "ECS/Systems/PhysicsSystems.h"

#include <glm/glm.hpp>

void UpdateMovementSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, moveComp] : world.View<PositionComponent, MoveComponent>().each())
	{
		glm::vec2 friction = glm::length(moveComp.Direction) > 0.0f ? glm::vec2(0.0f) : moveComp.Velocity * moveComp.Friction;

		glm::vec2 acceleration = moveComp.Direction * moveComp.Acceleration - friction;

		glm::vec2 newVelocity = moveComp.Velocity + acceleration * ts.GetDeltaTime();

		float speed = glm::length(newVelocity);

		if (speed > 0.0f)
		{
			moveComp.Velocity = glm::normalize(newVelocity) * glm::clamp(glm::length(newVelocity), -moveComp.MaxSpeed, moveComp.MaxSpeed);
		}
	
		positionComp.Position += moveComp.Velocity * ts.GetDeltaTime();
	}
}

void UpdateCollisionSystem(World& world, Chaos::Timestep ts)
{
	// First clear collisions from previous frame
	for (auto&& [entityID, collisionComp] : world.View<CollisionComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		entity.RemoveComponent<CollisionComponent>();
	}

	for (auto&& [entityID, positionComp, coliderComp, moveComp] : world.View<PositionComponent, CircleColliderComponent, MoveComponent>().each())
	{
		auto entity = Chaos::Entity(entityID, &world);

		auto position = positionComp.Position;
		auto radius = coliderComp.Radius;

		bool hasCollision = false;

		// Collision with world bounds
		if (position.x + radius >= world.GetBounds().Max.x)
		{
			auto& collision = entity.AddOrReplaceComponent<CollisionComponent>();
			collision.Position = { world.GetBounds().Max.x, position.y };
			collision.Normal = glm::vec2(-1.0f, 0.0f);
			hasCollision = true;
		}
		else if (position.x - radius <= world.GetBounds().Min.x)
		{
			auto& collision = entity.AddOrReplaceComponent<CollisionComponent>();
			collision.Position = { world.GetBounds().Min.x, position.y };
			collision.Normal = glm::vec2(1.0f, 0.0f);
			hasCollision = true;
		}

		if (position.y + radius >= world.GetBounds().Max.y)
		{
			auto& collision = entity.AddOrReplaceComponent<CollisionComponent>();
			collision.Position = { position.x, world.GetBounds().Max.y };
			collision.Normal = glm::vec2(0.0f, -1.0f);
			hasCollision = true;
		}
		else if (position.y - radius <= world.GetBounds().Min.y)
		{
			auto& collision = entity.AddOrReplaceComponent<CollisionComponent>();
			collision.Position = { position.x, world.GetBounds().Min.y };
			collision.Normal = glm::vec2(0.0f, 1.0f);
			hasCollision = true;
		}

		// Collision with other entities
		for (auto&& [otherEntityID, otherPositionComp, otherColiderComp] : world.View<PositionComponent, CircleColliderComponent>().each())
		{
			auto otherEntity = Chaos::Entity(otherEntityID, &world);

			if (entity == otherEntity) continue;

			auto otherPosition = otherPositionComp.Position;
			auto otherRadius = otherColiderComp.Radius;

			auto distance = glm::distance(position, otherPosition);

			if (distance <= radius + otherRadius)
			{
				// Add collision to current entity
				{
					auto& collision = entity.AddOrReplaceComponent<CollisionComponent>();
					auto direction = glm::normalize(otherPosition - position);
					collision.Entity = otherEntity;
					collision.Position = position + direction * radius;
					collision.Normal = direction * -1.0f;
					hasCollision = true;
				}

				// Add collision to other entity
				{
					auto& collision = otherEntity.AddOrReplaceComponent<CollisionComponent>();
					auto direction = glm::normalize(position - otherPosition);
					collision.Entity = entity;
					collision.Position = otherPosition + direction * otherRadius;
					collision.Normal = direction * -1.0f;
				}
			}
		}

		// Remove collision component if no collision was found
		if (!hasCollision && entity.HasComponent<CollisionComponent>())
		{
			entity.RemoveComponent<CollisionComponent>();
		}
	}

	// Clamp positions to world bounds
	for (auto&& [entityID, positionComp, coliderComp] : world.View<PositionComponent, CircleColliderComponent>().each())
	{
		positionComp.Position = glm::clamp(positionComp.Position,
			world.GetBounds().Min + coliderComp.Radius,
			world.GetBounds().Max - coliderComp.Radius);
	}
}

void UpdateCameraCollisionSystem(World& world, Chaos::Timestep ts)
{
	for (auto&& [entityID, positionComp, cameraComp] : world.View<PositionComponent, CameraComponent>().each())
	{
		auto size = cameraComp.Camera.GetOrthographicSize();
		auto aspectRation = cameraComp.Camera.GetAspectRatio();

		positionComp.Position = glm::clamp(positionComp.Position,
			world.GetBounds().Min + glm::vec2(size * aspectRation * 0.5f, size * 0.5f),
			world.GetBounds().Max - glm::vec2(size * aspectRation * 0.5f, size * 0.5f));
	}
}