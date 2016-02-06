#include <memory>

#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>

#include "../main/engine/Renderer.h"

class GLRenderer : public IRenderer
{

public:

    inline GLRenderer(std::shared_ptr<Engine> engine) : IRenderer(engine){};
    bool Init(uint32_t width, uint32_t height) override;
    void Draw() override;
    
private:
    
    GLFWwindow* window;

};