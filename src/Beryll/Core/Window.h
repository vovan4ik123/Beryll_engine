#pragma once

#include "LibsHeaders.h"
#include "CppHeaders.h"

namespace Beryll
{
    class Window
    {
    public:
        virtual ~Window() {}

        static void create();

        static void reCreate() { m_window->subReCreate(); };
        static void checkOrientationChange() { m_window->subCheckOrientationChange(); }; // if phone or tablet screen rotation allowed

        static uint32_t getScreenWidth() { return m_window->subGetScreenWidth(); }
        static uint32_t getScreenHeight() { return m_window->subGetScreenHeight(); }
        static SDL_Window* getWindow() { return m_window->subGetWindow(); }
        static SDL_GLContext* getGlContext() { return m_window->subGetGlContext(); }

        static void setClearColor(float r, float g, float b, float a) { m_window->subSetClearColor(r, g, b, a); }  // background color after clear()
        static void clear() { m_window->subClear(); }
        static void finishDraw() { m_window->subFinishDraw(); } // wait for finish all draw commands before swapWindow()
        static void flushDraw()  { m_window->subFlushDraw(); } // dont wait for finish draw commands before swapWindow()
        static void swapWindow() { m_window->subSwapWindow(); }

    protected:
        virtual void subReCreate() = 0;
        virtual void subCheckOrientationChange() = 0;

        virtual uint32_t subGetScreenWidth() = 0;
        virtual uint32_t subGetScreenHeight() = 0;
        virtual SDL_Window* subGetWindow() = 0;
        virtual SDL_GLContext* subGetGlContext() = 0;

        virtual void subSetClearColor(float r, float g, float b, float a) = 0;
        virtual void subClear() = 0;
        virtual void subFinishDraw() = 0;
        virtual void subFlushDraw() = 0;
        virtual void subSwapWindow() = 0;

    private:
        static std::unique_ptr<Window> m_window;
    };
}