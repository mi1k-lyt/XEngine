-- 方案名称
workspace "XEngine"
	-- 架构
	architecture "x64"
	startproject "DemoApp"
	-- 配置类型
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
-- 输出目录
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

-- 引擎项目
project "XEngine"
	-- 位置
	location "XEngine"
	-- 类型.dll
	kind "SharedLib"
	-- 语言类型
	language "C++"
	staticruntime "off"

	-- 目标输出目录
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- 中间输出目录
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- 预编译头文件
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

	-- 系统设置
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"XENGINE_PLATFORM_WINDOWS",
			"XENGINE_BUILD_DLL"
		}

		-- 将生成的dll文件copy到demo项目中
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/DemoApp")
		}

	-- 配置设置
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
	
-- 应用项目
project "DemoApp"
	-- 位置
	location "DemoApp"
	-- 类型控制台应用
	kind "ConsoleApp"
	-- 语言类型
	language "C++"

	-- 目标输出目录
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- 中间输出目录
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

	-- 链接项目
	links
	{
		"XEngine"
	}

	-- 系统设置
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"XENGINE_PLATFORM_WINDOWS"
		}

	-- 配置设置
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
	