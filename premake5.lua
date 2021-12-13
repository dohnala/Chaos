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

project "Chaos"
	location "Chaos"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
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
		"Chaos/src"
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