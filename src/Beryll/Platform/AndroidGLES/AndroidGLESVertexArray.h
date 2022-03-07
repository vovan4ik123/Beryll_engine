#pragma once

#include "Beryll/Renderer/VertexArray.h"

namespace Beryll
{
    class AndroidGLESVertexArray : public VertexArray
    {
    public:
        ~AndroidGLESVertexArray() override;

        void bind() override;
        void unBind() override;
        void draw() override;

        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertBuff) override;
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuff) override;

    private:
        friend class Renderer;
        AndroidGLESVertexArray();

        uint32_t m_VAO;
        uint32_t m_indexNumber = 0;
    };
}
