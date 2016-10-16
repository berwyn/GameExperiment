#pragma once

#include "renderer/renderer.h"

#ifdef EXPORTED
    #ifdef WINDOWS
        #define STATE __declspec(dllexport)
    #else
        #define STATE __attribute__ ((__visibility__("default")))
    #endif
#else
    #ifdef WINDOWS
        #define STATE __declspec(dllimport)
    #else
        #define STATE __attribute__ ((__visibility__("default")))
    #endif
#endif

#ifdef __cplusplus
    #define EXTERN extern "C"
#else
    #define EXTERN
#endif

///
/// \brief C API to load a renderer from a dylib
/// \return Returns an instance of Renderer or a nullptr
///
EXTERN STATE Game::Renderer* loadRenderer();
