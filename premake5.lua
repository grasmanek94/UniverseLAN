-- premake5.lua
workspace "lsfdrmfg"
    configurations { "Debug", "Release" }
    platforms { "x64" }
    location ""
    libdirs { "Build/%{cfg.platform}/%{cfg.buildcfg}" }
    targetdir "Build/%{cfg.platform}/%{cfg.buildcfg}"
 
    filter "platforms:x64"
        architecture "x64"
  
    filter "configurations:Debug"
        defines { "DEBUG" }
        flags { }
        cppdialect "C++14"
        symbols "On"
        staticruntime "On"
        optimize "Off"
        
    filter "configurations:Release"
        defines { "NDEBUG" }
        flags { "LinkTimeOptimization" }
        staticruntime "On"
        omitframepointer "On"
        cppdialect "C++14"
        optimize "Full"
        
project "ENet"
    kind "StaticLib"
    language "C++"
    location ""

    files { "Vendor/ENet/Source/**" }
    includedirs { "Vendor/ENet/Source/include" }

project "Common.Shared"
    kind "StaticLib"
    language "C++"
    location ""

    files { "Common/Common.Shared/**" }
    includedirs 
    { 
        "Vendor/ENet/Source/include",
        "Vendor/cereal-1.1.2/include",
        "Common/Common.Version",
        "Common/Common.Shared"
    }

project "Common.Version"
    kind "StaticLib"
    language "C++"
    location ""

    files { "Common/Common.Version/**" }
    includedirs { "Common/Common.Version" }

project "lsfdrmfg-svr"
    kind "ConsoleApp"
    language "C++"
    location ""
   
    files { "Server/Server.Application/**" }
    removefiles { "**.vcxproj", "**.filters", "**.user", "**.rc" }

    includedirs 
    { 
        "Vendor/ENet/Source/include",
        "Vendor/cereal-1.1.2/include",
        "Common/Common.Shared",
        "Server/Server.Application"     
    }
    
    links { "ENet" }
    links { "Common.Shared" }
    links { "Common.Version" }
