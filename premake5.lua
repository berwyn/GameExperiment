workspace "GameExperiment"
	configurations { "Debug", "Release" }
	
project "Game"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/"
	
	files { "src/**.hpp", "src/**.cpp", "src/shader/**" }
	
	filter "configurations:Debug"
		flags { "Symbols" }
		
	filter "system:windows"
		defines { "WIN32", "_WINDOWS", "_UNICODE", "UNICODE" }
		removefiles { "src/opengl/**", "src/shader/*.glsl" }
		links { "user32", "shell32", "dxgi" }
		
	filter "system:macosx"
		removefiles { "src/directx/**", "src/shader/*.hlsl" }