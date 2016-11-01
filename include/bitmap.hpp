#pragma once
#include <vector>
#include <linkage.hpp>

namespace tk {
    namespace graphics {

        template <class T>
        class Bitmap {
            std::vector<T> data;
            int width, height;
        public:

            Bitmap(int width, int height) : width(width), height(height) {
                data.resize(width * height);
            }

            Bitmap(int width, int height, T* data) : width(width), height(height) {
                data = std::vector(data, data + (width * height));
            }

            const T* getData() const {
                return data.data();
            }

            int getWidth() const {
                return width;
            }

            int getHeight() const {
                return height;
            }

            void blit(int x, int y, T* image, int w, int h) {
                for (int imageY = 0; imageY < h; ++imageY) {
                    for (int imageX = 0; imageX < w; ++imageX) {
                        if (x + imageX >= 0 && x + imageX < width && y + imageY >= 0 && y + imageY < height) {
                            at(x + imageX, y + imageY) = image[imageX + imageY * w];
                        }
                    }
                }
            }

            T& at(int x, int y) {
                return data[width * y + x];
            }
        };
    }
}