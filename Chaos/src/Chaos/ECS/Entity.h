#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/ECS/World.h"

#include <entt/entity/registry.hpp>

namespace Chaos
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(entt::entity id, World* world)
			: m_ID(id), m_World(world)
		{}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			CH_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_World->m_Registry.emplace<T>(m_ID, std::forward<Args>(args)...);
			return component;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = m_World->m_Registry.emplace_or_replace<T>(m_ID, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		const T& GetComponent() const
		{
			CH_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_World->m_Registry.get<T>(m_ID);
		}

		template<typename T>
		T& GetComponent()
		{
			CH_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_World->m_Registry.get<T>(m_ID);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_World->m_Registry.all_of<T>(m_ID);
		}

		template<typename T>
		void RemoveComponent()
		{
			CH_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_World->m_Registry.remove<T>(m_ID);
		}

		operator bool() const { return m_ID != entt::null; }
		operator entt::entity() const { return m_ID; }
		operator uint32_t() const { return (uint32_t)m_ID; }

		bool operator==(const Entity& other) const
		{
			return m_ID == other.m_ID && m_World == other.m_World;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_ID = entt::null;
		World* m_World = nullptr;
	};
}