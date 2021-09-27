#pragma once

#include "Beryll/Core/GameObject.h"

namespace Beryll
{
    // base class of all GUI objects
    class GUIObject : public GameObject
    {
    public:
        virtual ~GUIObject() {}

        // inherited pure virtual methods here

    protected:
        // add properties only for GUI objects
        uint32_t m_noBackgroundNoFrame = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;

        uint32_t m_backgroundNoFrame = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

        std::string m_soundID;
        bool m_needPlaySound = false;
    };
}
