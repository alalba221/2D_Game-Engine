workspace "Alalba_6160"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


--Include directories relatice to root folder (solution directory)
IncludeDir = {}
IncludeDir["Entt"] = "Alalba_6160/vendor/entt"
-- IncludeDir["Box2D"] = "Alalba_6160/vendor/Box2D/include"
-- IncludeDir["Glad"] = "Alalba/vendor/Glad/include"
-- IncludeDir["spdlog"] = "Alalba/vendor/spdlog/include"
-- IncludeDir["imgui"] = "Alalba/vendor/imgui"
-- IncludeDir["SDL"] = "Alalba/vendor/SDL"
IncludeDir["glm"] = "Alalba_6160/vendor/glm"
-- --startproject "Sandbox"
group"Dependencies"
	-- include "Alalba_6160/vendor/Box2D"
-- 	include "Alalba/vendor/Glad"
-- 	include "Alalba/vendor/imgui"
-- 	--include "Alalba/vendor/SDL"
group""


project "Alalba_6160"
	location "Alalba_6160"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "alalbapch.h"
	pchsource "alalbapch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src"
		, "%{IncludeDir.Entt}"
		-- ,"%{IncludeDir.spdlog}",
		-- "%{IncludeDir.Glad}",
		-- "%{IncludeDir.GLFW}",
		-- "%{IncludeDir.imgui}",
		, "%{IncludeDir.glm}"
		-- , "%{IncludeDir.Box2D}"
	}
	links
	{
		-- "Glad",
		-- "GLFW",
		"dl",
		"pthread",
		-- "ImGui",
		"SDL2",
		"SDL2_image",
		"SDL2_ttf"
		-- , "Box2D"
	}
	filter "system:linux"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "-fpermissive"
		defines
		{
			"ALALBA_PLATFORM_LINUX",
			"GLFW_INCLUDE_NONE"
			,"SDL_WINDOW_API"
		}

	filter "configurations:Debug"
		defines "ALALBA_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "ALALBA_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "ALALBA_Dist"
		optimize "On"