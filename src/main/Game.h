#include <memory>
#include <stdbool.h>

#include "engine/Engine.h"
#include "engine/IRenderer.h"

class Game
{

public:

    Game();

    bool Init(const char* rendererFlag);
    void Loop();
    void Terminate();

private:

    std::shared_ptr<Engine> engine;
    std::shared_ptr<IRenderer> renderer;
    
    void SetupRenderer(const char* rendererFlag);

};