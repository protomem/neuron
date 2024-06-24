workspace "neuron"
    configurations { "Debug", "Release" }
    architecture "x86_64"
    location "build"

project "neuron"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "build/%{cfg.buildcfg}"

    files { "src/**.cpp", "include/**.hpp" }
    includedirs { "include" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"