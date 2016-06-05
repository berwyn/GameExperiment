workspace "GameExperiment"
    configurations { "Debug", "Release" }
    location "build/"

    configuration "Debug"
        optimize "Debug"
        defines { "DEBUG" }
        flags "Symbols"
        targetdir "bin/debug"

    configuration "Release"
        targetdir "bin/release"

    filter "system:windows"
        defines { "WIN32", "WINDOWS", "_WINDOWS", "_UNICODE", "UNICODE" }

    filter "system:macosx"
        architecture "x86_64"
        defines { "APPLE" }
        buildoptions { "-std=c++14" }
        includedirs { "/usr/local/Cellar/glfw3/3.1.2/include" }
        libdirs { "/usr/local/Cellar/glfw3/3.1.2/lib" }

    filter "action:gmake"
        toolset "clang"

project "Game"
    kind "ConsoleApp"
    language "C++"

    links { "glfw3" }
    -- dependson { "DirectX", "OpenGL", "Metal", "Vulkan" }
    files { "src/main/**.h", "src/main/**.cpp" }

    includedirs { "vendor/cmdline" }

    -- Full path so NSight can function
    filter "configurations:Debug"
        debugdir "%{cfg.targetdir}"

    filter "system:windows"
        dependson { "DirectX", "OpenGL", "Vulkan" }
        links { "DirectX", "OpenGL", "Vulkan" }
        linkoptions {
            '/SUBSYSTEM:windows',
            '/ENTRY:mainCRTStartup' }

    filter "system:macosx"
        dependson { "OpenGL", "Metal" }
        links { "OpenGL", "Metal" }
        links {
            "CoreFoundation.framework",
            "Cocoa.framework",
            "OpenGL.framework",
            "Metal.framework",
            "MetalKit.framework",
            "IOKit.framework",
            "CoreVideo.framework" }

project "DirectX"
    kind "StaticLib"
    language "C++"

    filter "system:not windows"
        files { "src/dummy.cpp" }

    filter "system:windows"
        files { 
            "src/directx/**.h",
            "src/directx/**.cpp",
            "src/directx/**.hlsl"
        }

    filter "files:**.vs.hlsl"
        buildcommands {
            'fxc /Zi /Fo "%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso" /E "main" /T vs_5_0 /nologo %{file.relpath}'
        }

        buildoutputs { '%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso' }

    filter "files:**.ps.hlsl"
        buildcommands {
           'fxc /Zi /Fo "%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso" /E "main" /T ps_5_0 /nologo %{file.relpath}'
        }

        buildoutputs { '%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso' }

project 'OpenGL'
    kind 'StaticLib'
    language 'C++'

    files {
        'src/opengl/**.h',
        'src/opengl/**.cpp',
        'src/opengl/**.glsl'
    }

    includedirs {
        'vendor/glm' }

    filter 'system:macosx'
        links {
            'Cocoa.framework',
            'OpenGL.framework',
            'IOKit.framework',
            'CoreVideo.framework'
        }

    filter 'files:**.glsl'
        buildmessage 'Compiling %{file.relpath}'
        prebuildcommands {
            'mkdir -p %{cfg.targetdir}/assets/shaders'
        }

        buildcommands {
            'mkdir -p %{cfg.targetdir}/assets/shaders',
            'cp %{file.relpath} %{cfg.targetdir}/assets/shaders/'
        }

        buildoutputs { '%{cfg.targetdir}/assets/shaders/%{file.basename}.glsl' }

project "Metal"
    kind "StaticLib"
    language "C++"

    filter "system:macosx"
        files {
            "src/metal/**.h",
            "src/metal/**.hh",
            "src/metal/**.mm",
            "src/metal/**.metal" }
        links {
            "CoreFoundation.framework",
            "Cocoa.framework",
            "Metal.framework",
            "MetalKit.framework",
            "IOKit.framework",
            "CoreVideo.framework" }

project "Vulkan"
    kind "StaticLib"
    language "C++"

    filter "system:macosx"
        files { "src/dummy.cpp" }

    filter "system:not macosx"
        files { "src/vulkan/**.h", "src/vulkan/**.cpp" }
