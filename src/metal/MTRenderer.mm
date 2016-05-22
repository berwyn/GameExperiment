#include <stdbool.h>

#include "MTRenderer.hh"

MTRenderer::MTRenderer(std::shared_ptr<Engine> engine): IRenderer(engine)
{
    this->engine = engine;
}

MTRenderer::~MTRenderer(){}

bool MTRenderer::Init(uint32_t width, uint32_t height)
{
    NSRect rect = NSMakeRect(100, 100, width, height);
    NSUInteger mask = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;
    NSWindow* window = [[NSWindow alloc]
                        initWithContentRect:rect
                        styleMask:mask
                        backing:NSBackingStoreBuffered
                        defer:false];

    [window setTitle: @"GameExperiment"];
    [window setBackgroundColor:[NSColor blackColor]];
    [window setLevel:NSNormalWindowLevel];
    [window setHasShadow:false];
    this->window = window;
    
    MTKView* view = [[MTKView alloc]
                     initWithFrame:window.contentLayoutRect
                     device:MTLCreateSystemDefaultDevice()];

    view.paused = YES;
    view.enableSetNeedsDisplay = NO;
    this->view = view;
    
    [window setContentView:view];
    [window makeKeyAndOrderFront:window];
    return true;
}

void MTRenderer::Draw()
{
    [this->view draw];
}