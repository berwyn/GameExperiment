workspace "GameExperiment"
	configurations { "Debug", "Release" }
	
project "Game"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/"
	
	files { "src/**.h", "src/**.cpp", "src/shader/**" }
	
	filter "configurations:Debug"
        	defines { "DEBUG" }
		flags { "Symbols" }
		
	filter "system:windows"
		defines { "WIN32", "WINDOWS", "_WINDOWS", "_UNICODE", "UNICODE" }
		removefiles { "src/opengl/**", "src/shader/*.glsl" }

	filter "files:**.hlsl"
		buildcommands {
			'fxc /Fo "%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso" /E "main" /T vs_5_0 /nologo %{file.relpath}'
		}
		buildoutputs { '%{cfg.targetdir}\\assets\\shaders\\%{file.basename}.cso' }
		
	filter "system:macosx"
		removefiles { "src/directx/**", "src/shader/*.hlsl" }
