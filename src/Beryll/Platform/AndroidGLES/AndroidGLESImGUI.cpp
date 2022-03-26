#include "AndroidGLESImGUI.h"
#include "Beryll/Core/Window.h"
#include "Beryll/Utils/File.h"
#include "Beryll/GUI/Button.h"
#include "Beryll/GUI/CheckBox.h"
#include "Beryll/GUI/Text.h"

namespace Beryll
{
    AndroidGLESImGUI::AndroidGLESImGUI()
    {
        init();
    }

    AndroidGLESImGUI::~AndroidGLESImGUI()
    {
        destroy();
    }

    void AndroidGLESImGUI::init()
    {
        if(ImGui::GetCurrentContext())
        {
            return;
        }

        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(Window::getInstance()->getWindow(), Window::getInstance()->getGlContext());
        ImGui_ImplOpenGL3_Init(); // glsl_version = "#version 300 es" = default

        // complete initialization calling first frame
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(Window::getInstance()->getWindow());
        ImGui::NewFrame();
        // Rendering ImGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // load fonts
        uint32_t bufferSize = 0;
        char* buffer = nullptr;

        if(!m_defaultFontPath.empty() && m_defaultFontHeight != 0.0f)
        {
            buffer = File::readToBuffer(m_defaultFontPath.c_str(), &bufferSize);
            ImFont* fontDefault = io.Fonts->AddFontFromMemoryTTF(buffer, bufferSize, m_defaultFontHeight  * ImGui::GetIO().DisplaySize.y);
            BR_ASSERT((fontDefault != nullptr), "font nullptr");
            ImGui_ImplOpenGL3_CreateFontsTexture();
            ImGui::GetIO().FontDefault = fontDefault;
        }
        else
        {
            buffer = File::readToBuffer("fonts/roboto.ttf", &bufferSize); // load from ...../aseets/fonts/ folder
            ImFont* fontDefault = io.Fonts->AddFontFromMemoryTTF(buffer, bufferSize, 60);
            BR_ASSERT((fontDefault != nullptr), "font nullptr");
            ImGui_ImplOpenGL3_CreateFontsTexture();
            io.FontDefault = fontDefault;
        }

        if(!Button::fontPath.empty() && Button::fontHeight != 0.0f)
        {
            buffer = File::readToBuffer(Button::fontPath.c_str(), &bufferSize);
            ImFont* f = io.Fonts->AddFontFromMemoryTTF(buffer, bufferSize, Button::fontHeight * ImGui::GetIO().DisplaySize.y);
            BR_ASSERT((f != nullptr), "font nullptr");
            ImGui_ImplOpenGL3_CreateFontsTexture();
            Button::font = f;
        }
        else
        {
            Button::font = nullptr;
        }

        if(!CheckBox::fontPath.empty() && CheckBox::fontHeight != 0.0f)
        {
            buffer = File::readToBuffer(CheckBox::fontPath.c_str(), &bufferSize);
            ImFont* f = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(buffer, bufferSize, CheckBox::fontHeight * ImGui::GetIO().DisplaySize.y);
            BR_ASSERT((f != nullptr), "font nullptr");
            ImGui_ImplOpenGL3_CreateFontsTexture();
            CheckBox::font = f;
        }
        else
        {
            CheckBox::font = nullptr;
        }

        if(!Text::fontPath.empty() && Text::fontHeight != 0.0f)
        {
            buffer = File::readToBuffer(Text::fontPath.c_str(), &bufferSize);
            ImFont* f = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(buffer, bufferSize, Text::fontHeight * ImGui::GetIO().DisplaySize.y);
            BR_ASSERT((f != nullptr), "font nullptr");
            ImGui_ImplOpenGL3_CreateFontsTexture();
            Text::font = f;
        }
        else
        {
            Text::font = nullptr;
        }
    }

    void AndroidGLESImGUI::destroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void AndroidGLESImGUI::reCreate()
    {
        destroy();
        init();
    }

    void AndroidGLESImGUI::beginFrame()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(Window::getInstance()->getWindow());
        ImGui::NewFrame();
    }

    void AndroidGLESImGUI::endFrame()
    {
        // Rendering ImGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    float AndroidGLESImGUI::getGUIWidth()
    {
        return ImGui::GetIO().DisplaySize.x;
    }

    float AndroidGLESImGUI::getGUIHeight()
    {
        return ImGui::GetIO().DisplaySize.y;
    }

    void AndroidGLESImGUI::setDefaultFont(const char* path, float heightInPercent)
    {
        m_defaultFontPath = path;
        m_defaultFontHeight = heightInPercent / 100.0f;

        uint32_t bufferSize = 0;
        char *buffer = File::readToBuffer(m_defaultFontPath.c_str(), &bufferSize);
        ImFont* fontDefault = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(buffer, bufferSize, m_defaultFontHeight);
        BR_ASSERT((fontDefault != nullptr), "font nullptr");
        ImGui_ImplOpenGL3_CreateFontsTexture();
        ImGui::GetIO().FontDefault = fontDefault;
    }

    void AndroidGLESImGUI::setButtonsFont(const char* path, float heightInPercent)
    {
        Button::fontPath = path;
        Button::fontHeight = heightInPercent / 100.0f;

        uint32_t bufferSize = 0;
        char *buffer = File::readToBuffer(Button::fontPath.c_str(), &bufferSize);
        ImFont* f = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(buffer, bufferSize, Button::fontHeight * ImGui::GetIO().DisplaySize.y);
        BR_ASSERT((f != nullptr), "font nullptr");
        ImGui_ImplOpenGL3_CreateFontsTexture();
        Button::font = f;
    }

    void AndroidGLESImGUI::setCheckBoxesFont(const char* path, float heightInPercent)
    {
        CheckBox::fontPath = path;
        CheckBox::fontHeight = heightInPercent / 100.0f;

        uint32_t bufferSize = 0;
        char *buffer = File::readToBuffer(CheckBox::fontPath.c_str(), &bufferSize);
        ImFont* f = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(buffer, bufferSize, CheckBox::fontHeight * ImGui::GetIO().DisplaySize.y);
        BR_ASSERT((f != nullptr), "font nullptr");
        ImGui_ImplOpenGL3_CreateFontsTexture();
        CheckBox::font = f;
    }

    void AndroidGLESImGUI::setTextsFont(const char* path, float heightInPercent)
    {
        Text::fontPath = path;
        Text::fontHeight = heightInPercent / 100.0f;

        uint32_t bufferSize = 0;
        char *buffer = File::readToBuffer(Text::fontPath.c_str(), &bufferSize);
        ImFont* f = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(buffer, bufferSize, Text::fontHeight * ImGui::GetIO().DisplaySize.y);
        BR_ASSERT((f != nullptr), "font nullptr");
        ImGui_ImplOpenGL3_CreateFontsTexture();
        Text::font = f;
    }
}