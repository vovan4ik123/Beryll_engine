#pragma once

#include "GUIObject.h"
#include "Beryll/Core/SoundsManager.h"

namespace Beryll
{
    class Button : public GUIObject
    {
    public:
        // position and size in percent 0...100% of screen
        Button(const char* text, float left, float top, float width, float height, bool actRepeat = false);
        ~Button();

        virtual void updateBeforePhysics() override;
        virtual void updateAfterPhysics() override;
        virtual void draw() override;
        virtual void playSound() override;

        bool getIsPressed() { return m_pressed; }

        void setAction(std::function<void()> fn) { m_action = fn; }
        void setColor(float r, float g, float b, float a) { m_color = ImVec4{ r, g, b, a }; }
        void setClickedColor(float r, float g, float b, float a)  { m_clickedColor = ImVec4{ r, g, b, a }; }
        void setFontColor(float r, float g, float b, float a) { m_fontColor = ImVec4{ r, g, b, a }; }
        void setSoundWAV(const char* path) { SoundsManager::loadWAV(path);  m_soundID = path;  }

        static ImFont* font; // one font for all buttons
        static std::string fontPath;
        static float fontHeight; // in range 0 = 0%...1 = 100% of screen size

    private:
        // if action is set m_action() will called when clicked
        // can be called many times if m_flags contains ImGuiButtonFlags_Repeat
        // ImGuiButtonFlags_Repeat = button react on touch all time during finger is down
        std::function<void()> m_action;

        bool m_pressed = false; // if you want true all time during button touched pass actRepeat = true
        bool m_actRepeat = false;
        bool m_touched = false;

        std::string m_text;

        float m_leftPos; // in range 0 = 0%...1 = 100% of screen size
        float m_topPos;
        float m_width;
        float m_height;

        // collor can be different for each button
        ImVec4 m_fontColor = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f }; // 0.0f - 1.0f range
        ImVec4 m_color = ImVec4{ 0.4f, 0.4f, 0.4f, 1.0f };
        ImVec4 m_clickedColor = ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f };

        static uint32_t m_allButtonsCount;
    };
}