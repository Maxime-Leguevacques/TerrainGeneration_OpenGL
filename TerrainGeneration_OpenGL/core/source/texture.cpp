#include "texture.h"
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

Texture::Texture(unsigned int _texName)
    :texName(_texName)
{
}
 
void Texture::LoadTexture(const char* _path)
{
    std::string filePath(_path);
    std::cout << filePath << std::endl;
    std::string extension = filePath.substr(filePath.find_last_of(".") + 1);

    int width, height, nrChannels;

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load(_path, &width, &height, &nrChannels, 0);
    if (data) {
        if (extension == "jpg" || extension == "jpeg")
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (extension == "png")
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    stbi_image_free(data);
}

unsigned int Texture::loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;

    return 0;
}

unsigned int Texture::GetTextureName()
{
    return texName;
}

void Texture::Bind()
{

}
