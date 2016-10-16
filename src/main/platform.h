#pragma once

#import <string>

namespace Game::Platform
{
    bool loadDylib(std::string& name, void* result);
    bool loadSymbol(std::string& name, void* dylib, void* result);
}
