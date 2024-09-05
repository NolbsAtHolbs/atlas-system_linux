#include "multithreading.h"

/**
 * blur_portion - Blurs a portion of an image using a Gaussian blur
 * @portion: Pointer to the portion of the image and the blur settings
 */
void blur_portion(blur_portion_t const *portion)
{
    size_t x, y, i, j;
    size_t kernel_center = portion->kernel->size / 2;
    float red, green, blue, weight;
    pixel_t *pixel;

    for (y = portion->y; y < portion->y + portion->h; y++)
    {
        for (x = portion->x; x < portion->x + portion->w; x++)
        {
            red = green = blue = 0.0;

            for (i = 0; i < portion->kernel->size; i++)
            {
                for (j = 0; j < portion->kernel->size; j++)
                {
                    size_t pixel_x = (x + j >= kernel_center) ? (x + j - kernel_center) : 0;
                    size_t pixel_y = (y + i >= kernel_center) ? (y + i - kernel_center) : 0;

                    if (pixel_x >= portion->img->w)
                        pixel_x = portion->img->w - 1;
                    if (pixel_y >= portion->img->h)
                        pixel_y = portion->img->h - 1;

                    pixel = &portion->img->pixels[pixel_y * portion->img->w + pixel_x];
                    weight = portion->kernel->matrix[i][j];

                    red += pixel->r * weight;
                    green += pixel->g * weight;
                    blue += pixel->b * weight;
                }
            }

            pixel = &portion->img_blur->pixels[y * portion->img->w + x];
            pixel->r = (uint8_t)red;
            pixel->g = (uint8_t)green;
            pixel->b = (uint8_t)blue;
        }
    }
}
