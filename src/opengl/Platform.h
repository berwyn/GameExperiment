#pragma once

#ifdef WINDOWS

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRA_LEAN
#include <Windows.h>

#endif

#ifndef APPLE
#include "GL\glew.h"
#endif

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_GLEXT
#include "GLFW/glfw3.h"