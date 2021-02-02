workspace "sdbf"
	configurations {"Release", "Debug"}

project "sdbf"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	includedirs {"src/", "include/"}
	files {"src/**.cpp", "src/**.c", "include/**.cpp", "include/**.c", "src/**.h", "src/**.hpp", "include/**.h", "include/**.hpp"}
	

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"

	filter "system:windows"
		defines {"SDBF_WINDOWS"}
		buildoptions "/std:c++latest"

	filter "system:linux"
		defines {"SDBF_LINUX"}
		buildoptions "--std=c++20"