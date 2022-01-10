workspace "Chaos"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "Chaos/vendor/spdlog/include"
IncludeDir["glfw"] = "Chaos/vendor/glfw/include"
IncludeDir["glad"] = "Chaos/vendor/glad/include"
IncludeDir["glm"] = "Chaos/vendor/glm"
IncludeDir["imgui"] = "Chaos/vendor/imgui"

include "Chaos/vendor/glfw"
include "Chaos/vendor/glad"
include "Chaos/vendor/imgui"

project "Chaos"
	location "Chaos"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CH_DIST"
		runtime "Release"
		optimize "on"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Chaos/src",
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Chaos"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CH_DIST"
		runtime "Release"
		optimize "on"