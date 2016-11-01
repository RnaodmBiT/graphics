#include <font.hpp>
#include <ft2build.h>
#include <locale>
#include <codecvt>
#include FT_FREETYPE_H

namespace tk {
    namespace graphics {

        static FT_Library library = nullptr;

        static FT_Library getLibrary() {
            if (!library) {
                FT_Init_FreeType(&library);
            }

            return library;
        }


        class Font::Impl {
            FT_Face face;

        public:

            Impl(const std::string& filename) {
                FT_New_Face(getLibrary(), filename.c_str(), 0, &face);
            }

            ~Impl() {
                FT_Done_Face(face);
            }

            core::Vec2i measureText(const std::string& text, int size) {
                core::Vec2i bounds;

                FT_Set_Pixel_Sizes(face, 0, size);

                std::wstring_convert<std::codecvt_utf8<uint32_t>, uint32_t> utf32conv;
                std::basic_string<uint32_t> utf32 = utf32conv.from_bytes(text);

                FT_GlyphSlot slot = face->glyph;
                FT_UInt prevIndex = 0;
                FT_Vector kerning;
                FT_Vector pen = { 0, -size * 64 };

                for (uint32_t c : utf32) {
                    FT_Set_Transform(face, nullptr, &pen);

                    FT_UInt index = FT_Get_Char_Index(face, c);
                    if (prevIndex) {
                        FT_Get_Kerning(face, prevIndex, index, FT_KERNING_DEFAULT, &kerning);
                        pen.x += kerning.x;
                    }

                    FT_Load_Glyph(face, index, FT_LOAD_RENDER);

                    bounds.x = std::max(bounds.x, slot->bitmap_left + slot->bitmap.width);
                    bounds.y = std::max(bounds.y, -slot->bitmap_top + slot->bitmap.rows);

                    pen.x += slot->advance.x;
                    pen.y += slot->advance.y;

                    prevIndex = index;
                }

                return bounds;
            }

            Bitmap<uint8_t> renderText(const std::string& text, int size) {
                FT_Set_Pixel_Sizes(face, 0, size);

                core::Vec2i bounds = measureText(text, size);
                Bitmap<uint8_t> image(bounds.x, bounds.y);

                std::wstring_convert<std::codecvt_utf8<uint32_t>, uint32_t> utf32conv;
                std::basic_string<uint32_t> utf32 = utf32conv.from_bytes(text);

                FT_GlyphSlot slot = face->glyph;
                FT_UInt prevIndex = 0;
                FT_Vector kerning;
                FT_Vector pen = { 0, -size * 64 };

                for (char32_t c : utf32) {
                    FT_Set_Transform(face, nullptr, &pen);

                    FT_UInt index = FT_Get_Char_Index(face, c);
                    if (prevIndex) {
                        FT_Get_Kerning(face, prevIndex, index, FT_KERNING_DEFAULT, &kerning);
                        pen.x += kerning.x;
                    }

                    FT_Load_Glyph(face, index, FT_LOAD_RENDER);

                    image.blit(slot->bitmap_left, -slot->bitmap_top, slot->bitmap.buffer, slot->bitmap.width, slot->bitmap.rows);

                    pen.x += slot->advance.x;
                    pen.y += slot->advance.y;

                    prevIndex = index;
                }

                return image;
            }

        };


        Font::Font(const std::string& filename) {
            impl = new Impl(filename);
        }

        Font::~Font() {
            delete impl;
        }

        core::Vec2i Font::measureText(const std::string& text, int size) {
            return impl->measureText(text, size);
        }

        Bitmap<uint8_t> Font::renderText(const std::string& text, int size) {
            return impl->renderText(text, size);
        }
    }
}
