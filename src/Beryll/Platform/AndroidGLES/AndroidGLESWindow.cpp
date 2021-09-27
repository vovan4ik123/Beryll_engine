#include "AndroidGLESWindow.h"
#include "Beryll/Core/EventHandler.h"
#include "Beryll/GUI/MainImGUI.h"

namespace Beryll
{
    AndroidGLESWindow::AndroidGLESWindow()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            BR_ASSERT(false, "SDL init error");
        }

        // SET ATTRIBUTE ONLY after initialize
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // set to 1 to require hardware acceleration
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // minimum number of bits for the red channel
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // minimum number of bits for the green channel
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // minimum number of bits for the blue channel
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // minimum number of bits in depth buffer; default 16

        // SDL antialiasing for real device. Dont work on emulator !!
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // enable antialiasing sdl
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // 0 4 8

        // fill native display resolution
        //SDL_GetDesktopDisplayMode(0, &m_DM);
        // fill new resolution if resolution was changed in fulscreen mode
        SDL_GetCurrentDisplayMode(0, &m_DM);
        m_screenWidth = m_DM.w;
        m_screenHeight = m_DM.h;

        // Create an application window with the following settings:
        m_window = SDL_CreateWindow("MainWindow",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    m_screenWidth, m_screenHeight,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);

        if(m_window == nullptr)
        {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

            m_window = SDL_CreateWindow("MainWindow",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        m_screenWidth, m_screenHeight,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);
        }

        BR_ASSERT((m_window != nullptr), "m_window == nullptr");

        m_glContext = SDL_GL_CreateContext(m_window);
        SDL_GL_MakeCurrent(m_window, m_glContext);

        int vsync = SDL_GL_SetSwapInterval(-1); // Enable adaptive vsync
        if(vsync == -1) { SDL_GL_SetSwapInterval(1); } // Enable standart vsync

        glViewport(0, 0, m_screenWidth, m_screenHeight);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // src alpha for src color, 1 - src alpha for destination color

        BR_INFO("AndroidGLESWindow created and initialized. width:{0}, height:{1}", m_screenWidth, m_screenHeight);
    }

    AndroidGLESWindow::~AndroidGLESWindow()
    {
        SDL_GL_DeleteContext(m_glContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        BR_INFO("AndroidGLESWindow destroyed + SDL_Quit");
    }

    void AndroidGLESWindow::subReCreate()
    {
        SDL_DestroyWindow(m_window);

        SDL_GetCurrentDisplayMode(0, &m_DM);
        m_screenWidth = m_DM.w;
        m_screenHeight = m_DM.h;

        //SDL_GetDesktopDisplayMode(0, &m_DM); // native display resolution

        m_window = SDL_CreateWindow("MainWindow",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    m_screenWidth, m_screenHeight,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);

        BR_ASSERT((m_window != nullptr), "m_window == nullptr");

        SDL_GL_MakeCurrent(m_window, m_glContext); // set old context for new window

        int vsync = SDL_GL_SetSwapInterval(-1); // Enable adaptive vsync
        if(vsync == -1) { SDL_GL_SetSwapInterval(1); } // Enable standart vsync

        glViewport(0, 0, m_screenWidth, m_screenHeight); // for current resolution
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        BR_INFO("AndroidGLESWindow re created. width:{0}, height:{1}", m_screenWidth, m_screenHeight);
    }

    void AndroidGLESWindow::subCheckOrientationChange()
    {
        if(EventHandler::checkEvent(EventID::DISPLAY_ORIENTATION_CHANGE))
        {
            EventHandler::resetEvents(EventID::DISPLAY_ORIENTATION_CHANGE);
            Window::reCreate();
            MainImGUI::reCreate();
        }
    }
}

