
workspace "TicTacToe"
    configurations { "Debug", "Release" }
    architecture "x64"
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    project "TicTacToe"
        location "./"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files { "**.h", "**.hpp", "**.c", "**.cpp" }

        filter "system:windows"
            defines "MEF_WIN"

        filter "configurations:Debug"
            defines "DEBUG"
            optimize "Off"
            symbols "On"
        
        filter "configurations:Release"
            defines "RELEASE"
            optimize "On"


