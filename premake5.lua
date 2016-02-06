workspace "GameExperiment"
    configurations { "Debug", "Release" }

project "Game"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/"
    dependson { "Shaders" }

    files { "src/**.h", "src/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        flags { "Symbols" }
        debugdir "bin/"

    filter "system:windows"
        defines { "WIN32", "WINDOWS", "_WINDOWS", "_UNICODE", "UNICODE" }
        removefiles { "src/opengl/**", "src/shader/glsl/**" }

    filter "system:macosx"
        architecture "x86_64"
        removefiles { "src/directx/**", "src/shader/hlsl/**" }
        defines { "APPLE" }
        links { "glfw3", "Cocoa.framework", "OpenGL.framework", 
                "IOKit.framework", "IOKit.framework", "CoreVideo.framework" }
        buildoptions { "--std=c++14", "-I/usr/local/Cellar/glfw3/3.1.2/include/" }
        linkoptions { "-L/usr/local/Cellar/glfw3/3.1.2/lib" }

project "Shaders"
    kind "StaticLib"
    language "C++"
    targetdir "bin/"

    files { "src/shader/**" }

    filter "system:windows"
        removefiles { "src/shader/glsl/**" }

    filter "system:macosx"
        removefiles { "src/shader/hlsl/**" }
        
    filter "files:**.glsl"
        buildmessage 'Compiling %{file.relpath}'
        prebuildcommands {
            'mkdir -p %{cfg.targetdir}/assets/shaders'
        }
        buildcommands {
            'cp %{file.relpath} %{cfg.targetdir}/assets/shaders/'
        }
        buildoutputs { '%{cfg.targetdir}/assets/shaders/%{file.basename}.glsl' }

    filter "files:**.vs.hlsl"
        buildcommands {
            'fxc /Fo "%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso" /E "main" /T vs_5_0 /nologo %{file.relpath}'
        }

        buildoutputs { '%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso' }

    filter "files:**.ps.hlsl"
        buildcommands {
           'fxc /Fo "%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso" /E "main" /T ps_5_0 /nologo %{file.relpath}'
        }

        buildoutputs { '%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso' }

