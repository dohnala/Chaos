#pragma once

#include "Chaos/Core/Window.h"
#include "Chaos/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Chaos
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual float GetTime() const override;

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			uint32_t Width;
			uint32_t Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}