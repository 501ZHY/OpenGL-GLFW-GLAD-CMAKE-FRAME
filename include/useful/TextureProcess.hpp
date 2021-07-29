#pragma once

#include <glad/glad.h>
#include <string>
#include "useful/stb_image.h"
#include <iostream>

class TextureProcess
{
    private:
        

    public:

        TextureProcess()
        {}

        ~TextureProcess(){}

       static unsigned int loadTexture(char const* path,
                                    GLint wrap_s,GLint wrap_t,
                                    GLint filter_min,GLint filter_mag);

};

unsigned int TextureProcess::loadTexture(char const* path,
                                    GLint wrap_s=GL_REPEAT,GLint wrap_t=GL_REPEAT,
                                    GLint filter_min=GL_LINEAR_MIPMAP_LINEAR,GLint filter_mag=GL_LINEAR)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned int textureID;
    glGenTextures(1,&textureID);

    int width,height,nrChannel;
    unsigned char *data=stbi_load(path,&width,&height,&nrChannel,0);
    if(data)
    {
        GLenum format;
        if(nrChannel==1)
            format=GL_RED;
        else if(nrChannel==3)
            format=GL_RGB;
        else if(nrChannel==4)
            format=GL_RGBA;


        glBindTexture(GL_TEXTURE_2D,textureID);
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wrap_s);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrap_t);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filter_min);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filter_mag);

        stbi_image_free(data);
    }
    else
    {
        std::cout<<"Texture Failed to Load at path : "<<path<<std::endl;
        stbi_image_free(data);
    }
    return textureID;
}

