#pragma once
#include <linkage.hpp>
#include <string>
#include <bitmap.hpp>
#include <vector.hpp>
#include <resource.hpp>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Font : public core::IResource {
            class Impl;
            Impl* impl;
        public:

            Font(const std::string& filename);
            ~Font();

            static IResource* loadFromFile(const std::string& filename);

            core::Vec2i measureText(const std::string& text, int size);
            Bitmap<uint8_t> renderText(const std::string& text, int size);

        };

    }
}
