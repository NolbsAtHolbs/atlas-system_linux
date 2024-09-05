#include "multithreading.h"

/**
 * blur_pixel - Blurs a single pixel using the convolution kernel
 * @portion: Structure with blur information
 * @x: X position of the pixel to blur
 * @y: Y position of the pixel to blur
 */
void blur_pixel(blur_portion_t const *portion, size_t x, size_t y)
{
	float r = 0, g = 0, b = 0;
	size_t i, j, kx, ky;
	int x_offset, y_offset;
	int half_kernel = portion->kernel->size / 2;
	pixel_t *src_pixel, *dst_pixel;

	for (i = 0; i < portion->kernel->size; i++)
	{
		for (j = 0; j < portion->kernel->size; j++)
		{
			/* Calculate the pixel position */
			x_offset = x + (i - half_kernel);
			y_offset = y + (j - half_kernel);

			/* Ensure the pixel is within bounds */
			if (x_offset >= 0 && x_offset < (int)portion->img->w &&
				y_offset >= 0 && y_offset < (int)portion->img->h)
			{
				src_pixel = &portion->img->pixels[y_offset * portion->img->w + x_offset];
				r += src_pixel->r * portion->kernel->matrix[i][j];
				g += src_pixel->g * portion->kernel->matrix[i][j];
				b += src_pixel->b * portion->kernel->matrix[i][j];
			}
		}
	}

	/* Set the blurred pixel */
	dst_pixel = &portion->img_blur->pixels[y * portion->img->w + x];
	dst_pixel->r = (uint8_t)r;
	dst_pixel->g = (uint8_t)g;
	dst_pixel->b = (uint8_t)b;
}

/**
 * blur_portion - Blurs a portion of an image
 * @portion: Structure containing the portion and kernel information
 */
void blur_portion(blur_portion_t const *portion)
{
	size_t x, y;

	for (y = portion->y; y < portion->y + portion->h; y++)
	{
		for (x = portion->x; x < portion->x + portion->w; x++)
		{
			blur_pixel(portion, x, y);
		}
	}
}
