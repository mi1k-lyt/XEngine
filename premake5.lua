workspace "XEngine"
	architecture "x64"

	startproject "DemoApp"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



-- Include directories relative to root folder (Solution Directories)
IncludeDir = {}
IncludeDir["GLFW"] = "XEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "XEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "XEngine/vendor/imgui"
IncludeDir["glm"] = "XEngine/vendor/glm"

include "XEngine/vendor/GLFW"
include "XEngine/vendor/Glad"
include "XEngine/vendor/imgui"


project "XEngine"
	location "XEngine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")

	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	pchheader "Pch.h"
	pchsource "XEngine/src/Pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		-- Reason Why add Dwmapi.lib : https://stackoverflow.com/questions/10727627/dwmextendframeintoclientarea-dosent-work
		'Dwmapi.lib',
		"opengl32.lib"
	}

	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"XENGINE_PLATFORM_WINDOWS",
			"XENGINE_BUILD_DLL"
		}

		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/DemoApp")
		}


	filter "configurations:Debug"
		defines "XENGINE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "XENGINE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "XENGINE_DIST"
		buildoptions "/MD"
		optimize "On"
	

project "DemoApp"

	location "DemoApp"

	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"
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
		"XEngine/vendor/spdlog/include",
		"XEngine/src",
		"XEngine/vendor",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}


	links
	{
		"XEngine"
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"XENGINE_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "XENGINE_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "XENGINE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "XENGINE_DIST"
		runtime "Release"
		optimize "On"
	