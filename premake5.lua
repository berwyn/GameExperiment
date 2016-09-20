workspace 'GameExperiment'
    configurations { 'Debug', 'Release' }
    location 'build/'

    files { '.editorconfig' }
    architecture 'x86_64'

    configuration 'Debug'
        optimize 'Debug'
        defines { 'DEBUG' }
        flags 'Symbols'
        targetdir 'bin/debug'

    configuration 'Release'
        targetdir 'bin/release'

    -- Note:
    -- We're using C++17 here for the new filesystem APIs
    -- as well as the condensed namespaces. After C++17
    -- is finalised, these flags should be updated as
    -- clang/msvc standardise them

    filter 'system:macosx'
        defines { 'APPLE' }
        buildoptions { '-std=c++1z' }

    filter 'system:windows'
        defines { 'WIN32', 'WINDOWS', '_WINDOWS', '_UNICODE', 'UNICODE' }
        buildoptions { '/std:c++latest' }

    filter 'action:gmake'
        toolset 'clang'

project 'Game'
    kind 'ConsoleApp'
    language 'C++'

    files { 'src/main/**.h', 'src/main/**.cpp' }

    -- Full path so NSight can function
    filter 'configurations:Debug'
        debugdir '%{cfg.targetdir}'

    filter 'system:windows'
        linkoptions {
            '/SUBSYSTEM:windows',
            '/ENTRY:mainCRTStartup'
        }

if(os.is('windows')) then
    project 'DirectX'
        kind 'SharedLib'
        language 'C++'

        files { 'src/directx/*.h', 'src/directx/*.cpp' }
end

if(os.is("macosx")) then
    project 'Metal'
        kind 'SharedLib'
        language 'C++'

        files { 'src/metal/**.hh', 'src/metal/**.mm' }
end

if(os.is('not macosx')) then
    project 'Vulkan'
        kind 'SharedLib'
        language 'C++'

        files { 'src/vulkan/*.h', 'src/vulkan/*.cpp' }
end
