#include "texture.h"

#include <assert.h>

namespace Cell
{
    // ------------------------------------------------------------------------
    Texture::Texture()
    {
        
    }
    // ------------------------------------------------------------------------
    Texture::~Texture()
    {
        // TODO(Joey): this doesn't work as texture objects get frequently passed around over the
        // stack at which variables are copied and destructors are called; either manage the lifetime
        // over a single container, or do explicit texture cleanup.
        //glDeleteTextures(1, &m_ID);
    }
    // ------------------------------------------------------------------------
    void Texture::Generate(unsigned int width, GLenum format, GLenum type, unsigned char *data)
    {
        glGenTextures(1, &m_ID);

        Width = width;
        Height = 0;
        Depth = 0;
        Format = format;
        Type = type;

        assert(Target == GL_TEXTURE_1D);
        Bind();
            glTexImage1D(Target, 0, format, width, 0, format, type, data);
            glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, FilterMin);
            glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, FilterMax);
            glTexParameteri(Target, GL_TEXTURE_WRAP_S, WrapS);
            if(Mipmapping)
                glGenerateMipmap(Target);
        Unbind();
    }
    // ------------------------------------------------------------------------
    void Texture::Generate(unsigned int width, unsigned int height, GLenum format, GLenum type, unsigned char *data)
    {
        glGenTextures(1, &m_ID);

        Width = width;
        Height = height;
        Depth = 0;
        Format = format;
        Type = type;
        
        assert(Target == GL_TEXTURE_2D);
        Bind();
            glTexImage2D(Target, 0, format, width, height, 0, format, type, data);
            glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, FilterMin);
            glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, FilterMax);
            glTexParameteri(Target, GL_TEXTURE_WRAP_S, WrapS);
            glTexParameteri(Target, GL_TEXTURE_WRAP_T, WrapT);
            if (Mipmapping)
                glGenerateMipmap(Target);
        Unbind();
    }
    // ------------------------------------------------------------------------
    void Texture::Generate(unsigned int width, unsigned int height, unsigned int depth, GLenum format, GLenum type, unsigned char *data)
    {
        glGenTextures(1, &m_ID);

        Width = width;
        Height = height;
        Depth = depth;
        Format = format;
        Type = type;

        assert(Target == GL_TEXTURE_3D);
        Bind();
            glTexImage3D(Target, 0, format, width, height, depth, 0, format, type, data);
            glTexParameteri(Target, GL_TEXTURE_MIN_FILTER, FilterMin);
            glTexParameteri(Target, GL_TEXTURE_MAG_FILTER, FilterMax);
            glTexParameteri(Target, GL_TEXTURE_WRAP_S, WrapS);
            glTexParameteri(Target, GL_TEXTURE_WRAP_T, WrapT);
            glTexParameteri(Target, GL_TEXTURE_WRAP_R, WrapR);
            if (Mipmapping)
                glGenerateMipmap(Target);
        Unbind();
    }
    // ------------------------------------------------------------------------
    void Texture::Bind(int unit)
    {
        if(unit >= 0)
            glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(Target, m_ID);
    }
    // ------------------------------------------------------------------------
    void Texture::Unbind()
    {
        glBindTexture(Target, 0);
    }
}
