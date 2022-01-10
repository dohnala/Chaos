#pragma once

#include "Chaos/Core/Base.h"
#include "Chaos/Core/Timestep.h"
#include "Chaos/Events/Event.h"

namespace Chaos
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			: m_Name(name)
		{}

		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	};
}