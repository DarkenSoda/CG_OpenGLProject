#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>

class Texture {
public:
    unsigned int ID;
    int width, height, nrChannels;

    Texture(const char* path, GLint format);
    static void activate(GLenum textureUnit);
    void bind();
    void unbind();
};

#endif