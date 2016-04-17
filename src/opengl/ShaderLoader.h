#pragma once

#include <stdint.h>
#include <string>
#include <memory>

class ShaderLoader
{

public:
    
    static inline ShaderLoader& GetInstance()
    {
        static ShaderLoader instance;
        return instance;
    }
    
    /**
     * \brief Loads a shader from source code
     * \param type The GLenum type of this shader
     * \returns The GLuint ID of the shader
     */
    uint32_t LoadShaderFromSource(uint32_t type, std::string* name);
    
private:
    
    std::string loadSource(std::string* name);

};