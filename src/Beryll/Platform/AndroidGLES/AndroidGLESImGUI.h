#pragma once

#include "LibsHeaders.h"
#include "CppHeaders.h"

#include "Beryll/GUI/MainImGUI.h"
#include "Beryll/Core/Log.h"

namespace Beryll
{
    class AndroidGLESImGUI : public MainImGUI
    {
    public:
        ~AndroidGLESImGUI() override;

    private:
        friend class MainImGUI;
        AndroidGLESImGUI();

        void subBeginFrame() override;
        void subEndFrame() override;

        float subGetGUIWidth() override;
        float subGetGUIHeight() override;

        void subSetDefaultFont(const char* path, float heightInPercent) override;
        void subSetButtonsFont(const char* path, float heightInPercent) override;
        void subSetCheckBoxesFont(const char* path, float heightInPercent) override;
        void subSetTextsFont(const char* path, float heightInPercent) override;

        static std::string m_defaultFontPath;
        static float m_defaultFontHeight; // in range 0 = 0%...1 = 100% of screen size

        // Hide methods from base class
        static void create() { BR_ASSERT(false, "Use base class methods"); }
        static void reCreate() { BR_ASSERT(false, "Use base class methods"); }
        static void beginFrame() { BR_ASSERT(false, "Use base class methods"); }
        static void endFrame() { BR_ASSERT(false, "Use base class methods"); }
        static void setDefaultFont(ImFont* f) { BR_ASSERT(false, "Use base class methods"); }
        static float getGUIWidth() { BR_ASSERT(false, "Use base class methods"); return 0.0f; }
        static float getGUIHeight() { BR_ASSERT(false, "Use base class methods"); return 0.0f; }
        static void setDefaultFont(const char* path, float heightInPercent) { BR_ASSERT(false, "Use base class methods"); }
        static void setButtonsFont(const char* path, float heightInPercent) { BR_ASSERT(false, "Use base class methods"); }
        static void setCheckBoxesFont(const char* path, float heightInPercent) { BR_ASSERT(false, "Use base class methods"); }
        static void setTextsFont(const char* path, float heightInPercent) { BR_ASSERT(false, "Use base class methods"); }
    };
}