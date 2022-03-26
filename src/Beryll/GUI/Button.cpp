#include "Button.h"
#include "Beryll/Core/Log.h"
#include "Beryll/Core/EventHandler.h"
#include "MainImGUI.h"
#include "Beryll/Core/Window.h"

namespace Beryll
{
    Button::Button(const char* text, float left, float top, float width, float height, bool actRepeat)
        : m_text(text), m_leftPos(left / 100.0f), m_topPos(top / 100.0f), m_width(width / 100.0f), m_height(height / 100.0f)
    {
        BR_ASSERT((left >= 0.0f && left <= 100.0f) && (top >= 0.0f && top <= 100.0f)
                &&(width >= 0.0f && width <= 100.0f) && (height >= 0.0f && height <= 100.0f), "Wrong button size or position")

        m_actRepeat = actRepeat;

        m_ID = "Button_" + std::to_string(m_allButtonsCount);
        ++m_allButtonsCount;
    }

    Button::~Button()
    {

    }

    uint32_t Button::m_allButtonsCount = 0;
    ImFont* Button::font = nullptr;
    std::string Button::fontPath = std::string();
    float Button::fontHeight = 0.0f;

    void Button::updateBeforePhysics()
    {
        std::vector<Finger>& fingers = EventHandler::getFingers();

        if(fingers.empty())
        {
            m_pressed = false;
            m_touched = false;
        }
        else
        {
            if(m_actRepeat && m_pressed) // still keep button pressed or not
            {
                m_pressed = false;
                for(Finger& f : fingers)
                {
                    if(f.normalizedPos.x > m_leftPos && f.normalizedPos.x < m_leftPos + m_width
                       && f.normalizedPos.y > m_topPos && f.normalizedPos.y < m_topPos + m_height)
                    {
                        // if any finger in button area
                        m_pressed = true;
                    }
                }
            }
            else
            {
                m_pressed = false;
            }

            m_touched = false;
            for(Finger& f : fingers)
            {
                if(f.normalizedPos.x > m_leftPos && f.normalizedPos.x < m_leftPos + m_width
                   && f.normalizedPos.y > m_topPos && f.normalizedPos.y < m_topPos + m_height)
                {
                    // if any finger in button area
                    m_touched = true;

                    if(f.downEvent && !f.handled)
                    {
                        f.handled = true;
                        m_pressed = true;
                        m_needPlaySound = true;
                    }
                }
            }
        }

        if(m_pressed && m_action)
        {
            m_action();
        }
    }

    void Button::updateAfterPhysics()
    {

    }

    void Button::draw()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, m_color); // lost focus
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_color); // on focus
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_clickedColor); // clicked
        ImGui::PushStyleColor(ImGuiCol_Text, m_fontColor);


        ImGui::SetNextWindowPos(ImVec2(m_leftPos * MainImGUI::getInstance()->getGUIWidth(), m_topPos * MainImGUI::getInstance()->getGUIHeight()));
        ImGui::Begin(m_ID.c_str(), nullptr, m_noBackgroundNoFrame);

        if(font)
        {
            ImGui::PushFont(font);
            ImGui::Button(m_text.c_str(), ImVec2(m_width * MainImGUI::getInstance()->getGUIWidth(), m_height * MainImGUI::getInstance()->getGUIHeight()), ImGuiButtonFlags_PressedOnClick, &m_touched);
            ImGui::PopFont();
        }
        else
        {
            ImGui::Button(m_text.c_str(), ImVec2(m_width * MainImGUI::getInstance()->getGUIWidth(), m_height * MainImGUI::getInstance()->getGUIHeight()), ImGuiButtonFlags_PressedOnClick, &m_touched);
        }

        ImGui::End();

        ImGui::PopStyleColor(4);
    }

    void Button::playSound()
    {
        if( !m_soundID.empty() && m_needPlaySound)
        {
            m_needPlaySound = false;
            SoundsManager::playWAV(m_soundID);
        }
    }

}