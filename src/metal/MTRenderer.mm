#include "main/bind.h"
#include "MTRenderer.hh"

EXTERN STATE Game::Renderer* loadRenderer()
{
    auto renderer = new Game::Metal::MTRenderer();
    return renderer;
}

namespace Game::Metal
{
    auto MTRenderer::setup() -> bool
    {
        device = MTLCreateSystemDefaultDevice();
        return true;
    }
    
    auto MTRenderer::createWindow(uint32_t width, uint32_t height, WindowType type) -> bool
    {
        auto rect = CGRectMake(0, 0, width, height);
        auto mask = NSWindowStyleMaskTitled;
        window = [[NSWindow alloc]
                       initWithContentRect:rect
                       styleMask:mask
                       backing:NSBackingStoreNonretained
                       defer:NO];
        
        view = [[MTKView alloc]
                initWithFrame:window.contentLayoutRect
                device:MTLCreateSystemDefaultDevice()];
        
        [[window contentView] addSubview:view];
        [window makeKeyAndOrderFront:nil];
        return true;
    }
}
