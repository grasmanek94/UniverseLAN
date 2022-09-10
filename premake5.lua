-- premake5.lua
workspace "lsfdrmfg"
    configurations { "Debug", "Release" }
    platforms { "x64", "x86" }
    libdirs { "Build/%{cfg.platform}/%{cfg.buildcfg}" }
    targetdir "Build/%{cfg.platform}/%{cfg.buildcfg}"
    inheritdependencies "On"
    allmodulespublic "On"

    filter "platforms:x64"
        architecture "x64"

    filter "platforms:x86"
        architecture "x86"
  
    filter "configurations:Debug"
        defines { "DEBUG", "GALAXY_EXPORT" }
        flags { }
        cppdialect "C++14"
        symbols "On"
        staticruntime "On"
        optimize "Off"
        
    filter "configurations:Release"
        defines { "NDEBUG", "GALAXY_EXPORT" }
        flags { "LinkTimeOptimization" }
        staticruntime "On"
        omitframepointer "On"
        cppdialect "C++14"
        optimize "Full"
     
project "ENet"
    kind "StaticLib"
    language "C++"

    includedirs 
    { 
        "Vendor/ENet/Source/include",
        "Vendor/galaxy/Include/galaxy",
        "Vendor/cereal-1.1.2/include",
        "Common/Common.Version",
        "Common/Common.Shared",
    }

    files { "Vendor/ENet/Source/**" }

    filter "system:windows"
        defines { "_WINSOCK_DEPRECATED_NO_WARNINGS" }

    filter "system:unix"
        system "linux"

project "Common.Version"
    kind "StaticLib"
    language "C++"

    includedirs 
    { 
        "Vendor/ENet/Source/include",
        "Vendor/galaxy/Include/galaxy",
        "Vendor/cereal-1.1.2/include",
        "Common/Common.Version",
        "Common/Common.Shared"
    }

    filter { "system:windows" }
       prebuildcommands { "Util\\UpdateVersion.bat" }

    files { "Common/Common.Version/**" }

project "Common.Shared"
    kind "StaticLib"
    language "C++"

    includedirs 
    { 
        "Vendor/ENet/Source/include",
        "Vendor/galaxy/Include/galaxy",
        "Vendor/cereal-1.1.2/include",
        "Common/Common.Version",
        "Common/Common.Shared"
    }

    links { "ENet", "Common.Version" }
    files { "Common/Common.Shared/**" }


project "lsfdrmfg-client"
    kind "SharedLib"
    language "C++"

    includedirs 
    { 
        "Vendor/ENet/Source/include",
        "Vendor/galaxy/Include/galaxy",
        "Vendor/cereal-1.1.2/include",
        "Common/Common.Version",
        "Common/Common.Shared",
        "Client"
    }

    files { "Client/**" }
    removefiles { "**.vcxproj", "**.filters", "**.user", "**.rc" }
    
    links { "Common.Shared" }
 
    filter "system:windows"
        links {
         "Winmm",
         "ws2_32"
        }
   
    filter "platforms:x64"
        files { "Galaxy64.def" }
        targetname ("Galaxy64")

    filter "platforms:x86"
        files { "Galaxy.def" }
        targetname ("Galaxy")



project "lsfdrmfg-svr"
    kind "ConsoleApp"
    language "C++"

    includedirs 
    { 
        "Vendor/ENet/Source/include",
        "Vendor/galaxy/Include/galaxy",
        "Vendor/cereal-1.1.2/include",
        "Common/Common.Version",
        "Common/Common.Shared",
        "Server"
    }

    files { "Server/**" }
    removefiles { "**.vcxproj", "**.filters", "**.user", "**.rc" }

    links { "Common.Shared" }
 
    filter "system:windows"
        links {
         "Winmm",
         "ws2_32"
        }

    filter "platforms:x64"
        targetname ("GalaxyServer64")

    filter "platforms:x86"
        targetname ("GalaxyServer")



