/*****************************************************************//**
 * \file   Timer.hpp
 * \brief  Timer class
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace __XXECS
{
    class Timer
    {
    public:
        Timer() = default;

		void Restart()
        {
            m_start = clock::now();
        }

		std::chrono::microseconds Duration() const
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - m_start);
        }

    private:
		using clock = std::chrono::steady_clock;
        using timep = clock::time_point;
        timep m_start = clock::now();
    };
} 