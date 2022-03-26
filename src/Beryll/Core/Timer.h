#pragma once

#include "CppHeaders.h"

namespace Beryll
{
    class Timer
    {
    public:
        Timer() { }

        ~Timer() { }

        void reset()
        {
            m_start = std::chrono::system_clock::now();
        }

        float elapsedMilliSec()
        {
            return std::chrono::duration<float, std::milli>(std::chrono::system_clock::now() - m_start).count();
        }

        float elapsedSec()
        {
            return std::chrono::duration<float>(std::chrono::system_clock::now() - m_start).count();
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> m_start = std::chrono::system_clock::now();
    };
}