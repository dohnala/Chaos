#pragma once
#include "Chaos/Core/Layer.h"

#include "Chaos/Events/ApplicationEvent.h"
#include "Chaos/Events/KeyEvent.h"
#include "Chaos/Events/MouseEvent.h"

namespace Chaos {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		bool WantCaptureMouse();
		bool WantCaptueKeyboard();

		void Begin();
		void End();
	private:
		bool m_BlockEvents = true;
	};
}
