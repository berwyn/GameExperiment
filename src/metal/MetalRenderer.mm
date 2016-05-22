#include <stdbool.h>

#include "MetalRenderer.hh"

MetalRenderer::MetalRenderer(std::shared_ptr<Engine> engine): IRenderer(engine)
{
    this->engine = engine;
}

MetalRenderer::~MetalRenderer()
{
    
}

bool MetalRenderer::Init(uint32_t width, uint32_t height)
{
    NSWindow* window = [[NSWindow alloc]
                        initWithContentRect:NSMakeRect(100, 100, width, height)
                        styleMask:NSTitledWindowMask | NSMiniaturizableWindowMask
                        backing:NSBackingStoreBuffered
                        defer:NO];
    [window setTitle: @"GameExperiment"];
    this->window = window;
    
    MTKView* view = [[MTKView alloc]
                     initWithFrame:window.contentLayoutRect
                     device:MTLCreateSystemDefaultDevice()];
    view.paused = YES;
    view.enableSetNeedsDisplay = NO;
    this->view = view;
    
    window.contentView = view;
    return true;
}

void MetalRenderer::Draw()
{
    [this->view draw];
}