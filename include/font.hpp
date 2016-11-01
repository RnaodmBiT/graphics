#pragma once
#include <linkage.hpp>
#include <string>
#include <bitmap.hpp>
#include <vector.hpp>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Font {
            class Impl;
            Impl* impl;
        public:

            Font(const std::string& filename);
            ~Font();

            core::Vec2i measureText(const std::string& text, int size);
            Bitmap<uint8_t> renderText(const std::string& text, int size);

        };

    }
}