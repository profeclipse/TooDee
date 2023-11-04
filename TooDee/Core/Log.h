#pragma once

#include "TooDee/Core/Base.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#define GLM_ENABLE_EXPERIMENTAL
#ifdef TD_PLATFORM_MACOS
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)

namespace TooDee {
    class Log
    {
        public:
            static void Init();

            static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
        private:
            static Ref<spdlog::logger> s_CoreLogger;
            static Ref<spdlog::logger> s_ClientLogger;
    };
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
    return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
    return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
    return os << glm::to_string(quaternion);
}

// Core log macros
#define TD_CORE_TRACE(...)    ::TooDee::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TD_CORE_INFO(...)     ::TooDee::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TD_CORE_WARN(...)     ::TooDee::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TD_CORE_ERROR(...)    ::TooDee::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TD_CORE_CRITICAL(...) ::TooDee::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define TD_TRACE(...)         ::TooDee::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TD_INFO(...)          ::TooDee::Log::GetClientLogger()->info(__VA_ARGS__)
#define TD_WARN(...)          ::TooDee::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TD_ERROR(...)         ::TooDee::Log::GetClientLogger()->error(__VA_ARGS__)
#define TD_CRITICAL(...)      ::TooDee::Log::GetClientLogger()->critical(__VA_ARGS__)
