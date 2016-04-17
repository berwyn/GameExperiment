# GameExperiment
It's really as the name says -- I'm learning how to build a game engine.
The goal here is to learn C++14, RAII, graphics programming, and cross-platform
development in C++. If I'm very, very unlucky, I might also have to brush up
on my calculus and linear algebra.

## Prereqs


#### Windows
1. DirectX SDK
2. Visual Studio 2015
3. Premake 5 (`PS> scoop install premake5`)

#### OSX
1. XCode
2. GLFW (`$ brew install glfw`)
3. Premake5 (`$ brew install premake5`)

---

## Building

#### Windows
(Assuming you've used vcvars_all to place Visual Studio/MSBuild on your `PATH`)
```posh
PS> premake5 vs2015
PS> msbuild GameExperiment.sln
```
alternatively, to open in VS2015
```posh
PS> premake5 vs2015
PS> devenv GameExperiment.sln
```

#### OSX
```bash
$ premake5 xcode4
$ xcbuild GameExperiment.xcworkspace
```
alternatively, to open in XCode
```bash
$ premake5 xcode4
$ open GameExperiment.xcworkspace
```

---

## Structure

```
(root directory)
 |
 |-src              // Source code
 | |- main          // Platform agnostic and game logic code
 | |- directx       // DirectX 11 Renderer
 | |- opengl        // OpenGL 3.2 Renderer
 | `- shader        // HLSL/GLSL shaders
 |
 |- bin             // Compiled binaries
 |- obj             // Intermediary files
 `- premake5.lua    // Premake configuration file, generates projects
```

---

## FAQ

Q: `Why are you building an engine? Why not use Unreal/Unity/Frostbyte/etc`

A: If I were actually making a game, I would. But this is for learning
how engines like the ones mentioned work, as well as other low-level
graphics concepts.

Q: `Are you actually building a game? Will it be on Steam?`

A: Not really, and no.

Q: `Do you accept pull requests? Can I contribute?`

A: Yes! I do ask, however, that any pull requests highlight what they
add, or fix, and why. That way, people who come along later can learn
from my mistakes :p

Q: `What platforms does it run on?`

A: I test Windows 10 and OSX El Capitan. If it runs elsewhere, awesome!

Q: `What graphics pipeline do you use?`

A: DirectX 11 on Windows and OpenGL 3.2 on OSX. Eventually, I might look
and using DirectX 12 or Vulkan (respectively), but for now that's entirely
too low-level for my skillset.

Q: `What scripting engine are you using?`

A: For now, none. I'm investigating ChakraCore, LuaJIT, and Stackless Python.

Q: `What license is this under?`

A: Check below

---

MIT License

Copyright (c) 2015 berwyn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.