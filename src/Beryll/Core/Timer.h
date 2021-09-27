#pragma once

#include "CppHeaders.h"

namespace Beryll
{
    class Timer
    {
    public:
        Timer()
        {
            reset();
        }

        ~Timer()
        {

        }

        void reset()
        {
            m_start = std::chrono::system_clock::now();
        }

        float elapsedMilliSec()
        {
            std::chrono::duration<float, std::milli> elapsedMilliSec = std::chrono::system_clock::now() - m_start;

            return elapsedMilliSec.count();
        }

        float elapsedSec()
        {
            std::chrono::duration<float> elapsedSec = std::chrono::system_clock::now() - m_start;

            return elapsedSec.count();
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> m_start{};
    };
}