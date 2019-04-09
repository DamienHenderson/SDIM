-- Used for Visual Studio to determine the windows sdk version
system_ver = "10.0.17763.0"

-- Used to make the output directory nicer than the VS default
output_format = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "SDIM"
configurations {"Debug", "Release"}
platforms {"x86_64"}

--[[
project "SDIMCommon"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    location "%{prj.name}/"
    targetdir("bin/" .. output_format .. "/%{prj.name}")
    objdir("int/" .. output_format .. "/%{prj.name}")

    files {"%{prj.name}/**.cpp", "%{prj.name}/**.hpp"}

    filter "configurations:Debug"
        defines {"SDIMC_DEBUG"}
        symbols "On"
    filter "configurations:Release"
        defines {"SDIMC_RELEASE"}
        optimize "On"
    filter "platforms:x86"
        architecture "x86"
        defines {"SDIMC_X86"}
    filter "platforms:x86_64"
        architecture "x86_64"
        defines {"SDIMC_X86_64"}
    filter "system:windows"
        systemversion(system_ver)
    filter {}
]]--
project "Compiler"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    location "SDIM%{prj.name}/"
    targetdir("bin/" .. output_format .. "/%{prj.name}")
    objdir("int/" .. output_format .. "/%{prj.name}")

    files {"SDIM%{prj.name}/**.cpp", "SDIM%{prj.name}/**.hpp"}

    filter "configurations:Debug"
        defines {"SDIMC_DEBUG"}
        symbols "On"
    filter "configurations:Release"
        defines {"SDIMC_RELEASE"}
        optimize "On"
    filter "platforms:x86_64"
        architecture "x86_64"
        defines {"SDIMC_X86_64"}
    filter "system:windows"
        systemversion(system_ver)
    filter {}

project "VirtualMachine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    location "SDIM%{prj.name}/"
    targetdir("bin/" .. output_format .. "/%{prj.name}")
    objdir("int/" .. output_format .. "/%{prj.name}")

    files {"SDIM%{prj.name}/**.cpp", "SDIM%{prj.name}/**.hpp"}

    filter "configurations:Debug"
        defines {"SDIMVM_DEBUG"}
        symbols "On"
    filter "configurations:Release"
        defines {"SDIMVM_RELEASE"}
        optimize "On"
    filter "platforms:x86_64"
        architecture "x86_64"
        defines {"SDIMVM_X86_64"}
    filter "system:windows"
        systemversion(system_ver)
    filter {}
