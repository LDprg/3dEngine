/*****************************************************************/ /**
 * \file   Timer.hpp
 * \brief  Timer class
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace XXECS
{
    class Timer
    {
    public:
        Timer() = default;

        auto Restart() -> void
        {
            m_start = clock::now();
        }

        auto Duration() const -> std::chrono::microseconds
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - m_start);
        }

    private:
        typedef std::chrono::steady_clock clock;
        typedef clock::time_point timep;
        timep m_start = clock::now();
    };
}
