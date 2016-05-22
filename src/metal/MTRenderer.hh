#pragma once

#include <memory>

#ifdef __OBJC__

#include <Cocoa/Cocoa.h>
#include <MetalKit/MetalKit.h>

#endif

#include "../main/engine/Renderer.h"

class MTRenderer : public IRenderer
{

public:

    MTRenderer(std::shared_ptr<Engine> engine);
    ~MTRenderer();
    
    bool Init(uint32_t width, uint32_t height) override;
    void Draw() override;
    
private:
    std::shared_ptr<Engine> engine;
    
#ifdef __OBJC__
    NSWindow* window;
    MTKView* view;
#endif

};