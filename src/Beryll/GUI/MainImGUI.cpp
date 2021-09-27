#include "MainImGUI.h"
#include "Beryll/Platform/AndroidGLES/AndroidGLESImGUI.h"
#include "Beryll/Core/GameLoop.h"
#include "Beryll/Core/Log.h"

namespace Beryll
{
    std::unique_ptr<MainImGUI> MainImGUI::m_imGUI = nullptr;

    void MainImGUI::create()
    {
        BR_INFO("MainImGUI::create()");
        if(m_imGUI) { return; }

        if(GameLoop::getPlatform() == Platform::ANDROID_GLES)
        {
            m_imGUI = std::unique_ptr<MainImGUI>(new AndroidGLESImGUI());
        }
        else
        {
            BR_ASSERT(false, "Can not create ImGUI");
        }
    }

    void MainImGUI::reCreate()
    {
        BR_INFO("MainImGUI::reCreate()");

        if(GameLoop::getPlatform() == Platform::ANDROID_GLES)
        {
            m_imGUI = nullptr; // first call destructor
            m_imGUI = std::unique_ptr<MainImGUI>(new AndroidGLESImGUI());
        }
        else
        {
            BR_ASSERT(false, "Can not reCreate ImGUI");
        }
    }
}