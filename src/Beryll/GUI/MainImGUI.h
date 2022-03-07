#pragma once

#include "LibsHeaders.h"
#include "CppHeaders.h"

namespace Beryll
{
    // for all ImGUI elements
    // call MainImGUI::beginFrame() after Window::clear()
    // and before .draw() methods with any ImGUI element
    // call MainImGUI::endFrame() after .draw() methods with any ImGUI element
    // and before Window::finishDraw() and Window::swapWindow()
    class MainImGUI
    {
    public:
        virtual ~MainImGUI() {}

        static void create();
        static void reCreate();

        static void beginFrame() { m_imGUI->subBeginFrame(); }
        static void endFrame() { m_imGUI->subEndFrame(); }

        static float getGUIWidth() { return m_imGUI->subGetGUIWidth(); }
        static float getGUIHeight() { return m_imGUI->subGetGUIHeight(); }

        /*
        * path must skip assets/ folder and starts from next folder inside assets/
        * heightPercent - font height in percent 0%...100% of screen
        */
        static void setDefaultFont(const char* path, float heightInPercent) { m_imGUI->subSetButtonsFont(path, heightInPercent); }
        static void setButtonsFont(const char* path, float heightInPercent) { m_imGUI->subSetButtonsFont(path, heightInPercent); }
        static void setCheckBoxesFont(const char* path, float heightInPercent) { m_imGUI->subSetCheckBoxesFont(path, heightInPercent); }
        static void setTextsFont(const char* path, float heightInPercent) { m_imGUI->subSetTextsFont(path, heightInPercent); }

    protected:
        virtual void subBeginFrame() = 0;
        virtual void subEndFrame() = 0;

        virtual float subGetGUIWidth() = 0;
        virtual float subGetGUIHeight() = 0;

        virtual void subSetDefaultFont(const char* path, float heightInPercent) = 0;
        virtual void subSetButtonsFont(const char* path, float heightInPercent) = 0;
        virtual void subSetCheckBoxesFont(const char* path, float heightInPercent) = 0;
        virtual void subSetTextsFont(const char* path, float heightInPercent) = 0;

    private:
        static std::unique_ptr<MainImGUI> m_imGUI;
    };
}
