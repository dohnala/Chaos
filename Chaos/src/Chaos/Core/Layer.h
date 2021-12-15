#pragma once

#include "Chaos/Core/Base.h"

namespace Chaos
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;

		const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	};
}