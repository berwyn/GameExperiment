#include <cstdlib>
#include <iostream>
#include <thread>

#include "cmdline.h"
#include "Game.h"
#include "Logger.h"

#if defined(WINDOWS) && !defined(DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#ifdef WINDOWS
#include "../directx/DXRenderer.h"
#endif

#ifdef APPLE
#include "../metal/MetalRenderer.hh"
#endif

#include "../opengl/GLRenderer.h"

const char* getCmdOption(char** begin, char** end, const std::string& option)
{
    char** iter = std::find(begin, end, option);
    if(iter != end && ++iter != end)
    {
        return *iter;
    }
    return nullptr;
}

int main(int argc, char* argv[])
{
	const char* rendererFlag = getCmdOption(argv, argv + argc, "--renderer");
	
	auto game = Game();
	if(game.Init(rendererFlag))
	{
		game.Loop();
	}
	game.Terminate();
	return 0;
}

Game::Game()
{
	this->engine = std::make_shared<Engine>();
}

bool Game::Init(const char* rendererFlag)
{
	this->SetupRenderer(rendererFlag);
	if (!engine->Init(renderer))
	{
		auto message = std::make_unique<std::string>("Failed to initialize engine");
		Logger::GetInstance()->Fatal(message.get());
		return false;
	}
	return true;
}

void Game::Loop()
{
	while (!engine->ShouldHalt)
	{
		using namespace std::literals;
		// TODO: Do real things here
		engine->Frame();
	}
}

void Game::Terminate()
{

#ifdef DEBUG
	if (engine->IsInErrorState)
	{
		// TODO: Shutdown GUI but wait for input before closing console
	}
#endif

	engine->Shutdown();
}

void Game::SetupRenderer(const char* rendererFlag)
{
	std::shared_ptr<IRenderer> renderer = nullptr;
    
    if(rendererFlag == nullptr || strcmp("", rendererFlag))
    {
#ifdef WINDOWS
        renderer = std::make_shared<DXRenderer>(this->engine);
#else
        renderer = std::make_shared<GLRenderer>(this->engine);
#endif
    }
    else if(strcmp(rendererFlag, "directx"))
	{
#ifdef WINDOWS
		renderer = std::make_shared<DXRenderer>(this->engine);
#endif
	}
	else if(strcmp(rendererFlag, "opengl"))
	{
		renderer = std::make_shared<GLRenderer>(this->engine);
	}
	else if(strcmp(rendererFlag, "metal"))
	{
#ifdef APPLE
		renderer = std::make_shared<MetalRenderer>(this->engine);
#endif
	}
	else if(strcmp(rendererFlag, "vulkan"))
	{
#ifndef APPLE
		renderer = std::make_shared<VulkanRenderer>(this->engine);
#endif
	}
	else
	{
        exit(2);
	}
	
	if(renderer == nullptr)
	{
		exit(1);
	}
	
	this->renderer = renderer;
}