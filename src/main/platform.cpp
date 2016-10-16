#import "platform.h"

#ifdef APPLE

#define _DARWIN_BETTER_REALPATH
#import <stdlib.h>
#import <stdint.h>
#import <dlfcn.h>
#import <mach-o/dyld.h>

#endif

namespace Game::Platform
{
    auto buildPath(std::string& name) -> std::string
    {
#ifdef APPLE
        char path[1024];
        uint32_t size = sizeof(path);
        _NSGetExecutablePath(path, &size);
        
        auto real = realpath(path, nullptr);
        auto fullpath = std::string(real);
        
        free(real);
        free(path);
        
        return fullpath;
#endif
    }
    
    auto loadDylib(std::string& name, void* result) -> bool
    {
#ifdef APPLE
        auto path = buildPath(name);
        result = dlopen(path.c_str(), RTLD_LAZY);
        return result == nullptr;
#elif defined(LINUX)
        // TODO: Linux version of dlopen
#elif defined(WINDOWS)
        // TODO: LoadLibrary
#endif
    }
    
    auto loadSymbol(std::string& name, void* dylib, void* result) -> bool
    {
        return false;
    }
}
