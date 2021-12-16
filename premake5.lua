workspace "Chaos"
	architecture "x64"
	startproject "Example"

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

include "Chaos/vendor/glfw"
include "Chaos/vendor/glad"

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
	}

	links
	{
		"GLFW",
		"Glad",
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

project "Example"
	location "Example"
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
		"Chaos/vendor/spdlog/include"
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