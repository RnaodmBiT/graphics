#pragma once
#include <vector>
#include <linkage.hpp>

namespace tk {
    namespace graphics {

        /**
         * An abstraction of a 2D array of pixels of type T.
         * This class can be used to hold a 2D image in CPU memory.
         * It supports basic operations such as pixel access and image blitting.
         * This can be very useful for preparing an image for upload to the GPU and a Texture object.
         */
        template <class T>
        class Bitmap {
            std::vector<T> data;
            int width, height;
        public:

            /** Create a new bitmap with a set width and height. */
            Bitmap(int width, int height) : width(width), height(height) {
                data.resize(width * height);
            }

            /** Create a new bitmap with a set width and height and copy width*height pixels in. */
            Bitmap(int width, int height, T* data) : width(width), height(height) {
                data = std::vector<T>(data, data + (width * height));
            }

            /** Get a pointer to the internal image data. This can be useful for directly copying the data out. */
            const T* getData() const {
                return data.data();
            }

            /** Get the width of the bitmap image. */
            int getWidth() const {
                return width;
            }

            /** Get the height of the bitmap image. */
            int getHeight() const {
                return height;
            }

            /** Blit an image into this bitmap.
             * \param x The x coordinate of the top left corner where the image will be copied.
             * \param y The y coordinate of the top left corner where the image will be copied.
             * \param image A pointer to the data of the image that will be copied.
             * \param w The width of the image data to be copied.
             * \param h The height of the image data to be copied.
             */
            void blit(int x, int y, T* image, int w, int h) {
                for (int imageY = 0; imageY < h; ++imageY) {
                    for (int imageX = 0; imageX < w; ++imageX) {
                        if (x + imageX >= 0 && x + imageX < width && y + imageY >= 0 && y + imageY < height) {
                            at(x + imageX, y + imageY) = image[imageX + imageY * w];
                        }
                    }
                }
            }

            /** Get access to a specific pixel.
             * \param x The x coordinate of the pixel.
             * \param y The y coordinate of the pixel.
             * \return Returns a reference to the pixel at the given coordinate. */
            T& at(int x, int y) {
                return data[width * y + x];
            }
        };
    }
}
