workspace "TicketToRide_Map_Analyzer"
    architecture "x64"
    configurations { "Debug", "Release" }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include_dirs = {}
include_dirs["SPDLOG"] = "libs/SPDLOG/include"
include_dirs["TOML11"] = "libs/TOML11/include"

project "TicketToRide_Map_Analyzer"
    kind "ConsoleApp"
    language "C++"

    targetdir ( "bin/" .. output_dir .. "/%{prj.name}" )
    objdir ( "bin-int/" .. output_dir .. "/%{prj.name}" )

    files { "**.cpp", "**.h" }

    defines { "SPDLOG_COMPILED_LIB" }

    includedirs ( include_dirs )

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
