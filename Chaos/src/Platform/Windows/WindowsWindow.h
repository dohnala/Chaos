#pragma once

#include "Chaos/Core/Window.h"

namespace Chaos
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		uint32_t GetWidth() const override { return m_Data.Width; }
		uint32_t GetHeight() const override { return m_Data.Height; }
	private:
		struct WindowData
		{
			std::string Title;
			uint32_t Width;
			uint32_t Height;
		};

		WindowData m_Data;
	};
}