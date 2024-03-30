#pragma once

#include <string>
#include "TooDee/Core/Base.h"

namespace TooDee {
    enum class ImageFormat
    {
        None = 0,
        R8,
        RGB8,
        RGBA8,
        RGBA32F
    };

    class Texture
    {
        public:
            virtual ~Texture() = default;

            virtual uint32_t GetWidth() const = 0;
            virtual uint32_t GetHeight() const = 0;

            virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
        public:
            static Ref<Texture2D> Create(const std::string& path);
    };
}
