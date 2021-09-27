#pragma once

#include "LibsHeaders.h"
#include "CppHeaders.h"

namespace Beryll
{
    class TimeStep
    {
    public:
        static uint32_t getMillisecFromStart()
        {
            return SDL_GetTicks();
        }

        static float getSecFromStart()
        {
            return static_cast<float>(SDL_GetTicks()) / 1000.0f;
        }

        static void sleep(uint32_t millisec)
        {
            SDL_Delay(millisec);
        }

        static void fixateTime()
        {
            m_timeStepMIlliSec = SDL_GetTicks() - m_currentFrameStart;
            m_timeStepSec = m_timeStepMIlliSec / 1000.0f;

            m_currentFrameStart = SDL_GetTicks();
        }

        static float getTimeStepMilliSec()
        {
            return m_timeStepMIlliSec;
        }

        static float getTimeStepSec()
        {
            return m_timeStepSec;
        }

    private:
        static float m_currentFrameStart; // time in millisec
        static float m_timeStepMIlliSec; // time between previous frame start and current frame start
        static float m_timeStepSec; // time between previous frame start and current frame start
    };
}