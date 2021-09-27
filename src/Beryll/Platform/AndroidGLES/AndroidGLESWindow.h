#pragma once

#include "LibsHeaders.h"

#include "Beryll/Core/Window.h"
#include "Beryll/Core/Log.h"

#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>

namespace Beryll
{
    class AndroidGLESWindow : public Window
    {
    public:
        virtual ~AndroidGLESWindow();

    private:
        friend class Window;
        AndroidGLESWindow();

        virtual void subReCreate() override;
        virtual void subCheckOrientationChange() override; // if phone or tablet screen rotation allowed

        virtual uint32_t subGetScreenWidth() override { return m_screenWidth;}
        virtual uint32_t subGetScreenHeight() override { return m_screenHeight;}
        virtual SDL_Window* subGetWindow() override { return m_window; }
        virtual SDL_GLContext* subGetGlContext() override { return &m_glContext; }

        virtual void subSetClearColor(float r, float g, float b, float a) override
        {
            glClearColor(r, g, b, a);
        }
        virtual void subClear() override
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //	| GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
        }
        virtual void subFinishDraw() override // wait for finish all draw commands before swapWindow()
        {
            glFinish();
        }
        virtual void subFlushDraw() override // dont wait for finish draw commands before swapWindow()
        {
            glFlush();
        }
        virtual void subSwapWindow() override
        {
            SDL_GL_SwapWindow(m_window);
        }

        // Hide methods from base class
        static void create() { BR_ASSERT(false, "Use base class methods"); }
        static void reCreateWindow() { BR_ASSERT(false, "Use base class methods"); }
        static void checkOrientationChange() { BR_ASSERT(false, "Use base class methods"); }
        static uint32_t getScreenWidth() { BR_ASSERT(false, "Use base class methods"); return 0; }
        static uint32_t getScreenHeight() { BR_ASSERT(false, "Use base class methods"); return 0; }
        static SDL_Window* getWindow() { BR_ASSERT(false, "Use base class methods"); return nullptr; }
        static SDL_GLContext* getGlContext() { BR_ASSERT(false, "Use base class methods"); return nullptr; }
        static void setClearColor(float r, float g, float b, float a) { BR_ASSERT(false, "Use base class methods"); }
        static void clear() { BR_ASSERT(false, "Use base class methods"); }
        static void finishDraw() { BR_ASSERT(false, "Use base class methods"); }
        static void flushDraw() { BR_ASSERT(false, "Use base class methods"); }
        static void swapWindow() { BR_ASSERT(false, "Use base class methods"); }

        SDL_DisplayMode m_DM;
        SDL_Window* m_window = nullptr;
        SDL_GLContext m_glContext = nullptr;

        uint32_t m_screenWidth = 0;
        uint32_t m_screenHeight = 0;
    };
}
