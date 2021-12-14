#include "pch.h"
#include "Chaos/Core/Window.h"

#ifdef CH_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Chaos
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef CH_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			HZ_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif	
	}
}