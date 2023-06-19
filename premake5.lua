workspace "XEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "XEngine"
	location "XEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"XE_PLATFORM_WINDOWS",
			"XE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/DemoApp")
		}

	filter "configurations:Debug"
		defines "XE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "XE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "XE_DIST"
		optimize "On"
	
project "DemoApp"
	location "DemoApp"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"XEngine/vendor/spdlog/include",
		"XEngine/src"
	}

	links
	{
		"XEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"XE_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "XE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "XE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "XE_DIST"
		optimize "On"
	