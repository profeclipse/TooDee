#pragma once

namespace TooDee {
    class TimeStep
    {
        public:
            TimeStep(float time = 0.0f)
                : m_time(time)
            {
            }

            operator float() const { return m_time; }

            float GetSeconds() const { return m_time; }
            float GetMilliseconds() const { return m_time * 1000.0f; }
        private:
            float m_time;
    };
}
