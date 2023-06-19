-- 方案名称
workspace "XEngine"
	-- 架构
	architecture "x64"
	-- 配置类型
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
-- 输出目录
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 引擎项目
project "XEngine"
	-- 位置
	location "XEngine"
	-- 类型.dll
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	-- 系统设置
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"XE_PLATFORM_WINDOWS",
			"XE_BUILD_DLL"
		}

		-- 将生成的dll文件copy到demo项目中
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/DemoApp")
		}

	-- 配置设置
	filter "configurations:Debug"
		defines "XE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "XE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "XE_DIST"
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
		"XEngine/src"
	}

	-- 链接项目
	links
	{
		"XEngine"
	}

	-- 系统设置
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"XE_PLATFORM_WINDOWS"
		}

	-- 配置设置
	filter "configurations:Debug"
		defines "XE_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "XE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "XE_DIST"
		optimize "On"
	