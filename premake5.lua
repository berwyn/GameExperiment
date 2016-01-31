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
		removefiles { "src/opengl/**", "src/shader/*.glsl" }

	filter "system:macosx"
		removefiles { "src/directx/**", "src/shader/*.hlsl" }

project "Shaders"
    kind "SharedLib"
    language "C++"
    targetdir "bin/"

    files { "src/shader/**" }

    filter "system:windows"
        toolset "msc"
        removefiles { "src/shader/*.glsl", "src/shader/**/*.glsl" }

    filter "system:osx"
        removefiles { "src/shader/*.hlsl", "src/shader/**/*.hlsl" }

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

