#include "AndroidGLESTexture.h"
#include "Beryll/Core/Log.h"

#include "LibsHeaders.h"

#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>

namespace Beryll
{
    AndroidGLESTexture::AndroidGLESTexture(const char* path, uint32_t indexInShader)
    {
        try
        {
            std::string strPath = path;
            std::string extension = strPath.substr(strPath.find_last_of('.'));

            BR_ASSERT(((extension == ".png") || (extension == ".jpg")), "Supported only .png or .jpg textures");
        }
        catch(const std::out_of_range& e)
        {
            BR_ASSERT(false, "Texture does not have extension {0}", path);
        }

        // only two sampler2D supports for now (0 = diffuse, 1 = specular)
        BR_ASSERT(((indexInShader == 0) || (indexInShader == 1)), "Pass correct index of sampler2D for texture");

        m_indexInShader = indexInShader;

        auto result =  m_textures.find(std::string(path));
        if(result != m_textures.end())
        {
            // texture was added before
            // use it
            m_textureID = result->second;
            return;
        }

        SDL_RWops* rw = SDL_RWFromFile(path, "rb");
        BR_ASSERT((rw != nullptr), "Load texture failed: {0}", path);

        SDL_Surface* surface = IMG_Load_RW(rw, 1);
        BR_ASSERT((surface != nullptr), "Create surface failed: {0}", path);

        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        int pixelFormat = GL_RGB;
        if(4 == surface->format->BytesPerPixel) pixelFormat = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, surface->w, surface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, surface->pixels);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        m_textures.insert(std::make_pair(path, m_textureID)); // add to map
    }

    AndroidGLESTexture::~AndroidGLESTexture()
    {
        // keep textures in static map
    }

    std::map<std::string, uint32_t> AndroidGLESTexture::m_textures;

    void AndroidGLESTexture::bind()
    {
        if(m_indexInShader == 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_textureID);
        }
        else if(m_indexInShader == 1)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, m_textureID);
        }
    }

    void AndroidGLESTexture::unBind()
    {
        if(m_indexInShader == 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        else if(m_indexInShader == 1)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}