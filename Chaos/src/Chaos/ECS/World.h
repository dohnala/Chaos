#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Timestep.h"

#include <entt/entity/registry.hpp>

namespace Chaos
{
	class Entity;

	class World
	{
	public:
		World() = default;
		virtual ~World() = default;

		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		template<typename Component, typename... Other, typename... Exclude>
		entt::basic_view<entt::entity, entt::get_t<Component, Other...>, entt::exclude_t<Exclude...>> View(entt::exclude_t<Exclude...> = {})
		{
			return m_Registry.view<Component, Other...>(assure<Exclude>()...);
		}

		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnViewportResize(uint32_t width, uint32_t height) = 0;
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}