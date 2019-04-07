#include <blur.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNEL_NUM 3

int main(int argc, char **argv)
{
	int width, height, bpp;
	int r = 5;

	uint8_t *rgb_image = stbi_load(argv[1], &width, &height, &bpp, 3);

	uint8_t *rgb_image_w;
	rgb_image_w = malloc(width * height * CHANNEL_NUM);

	fast_gauss_blur(rgb_image, rgb_image_w, width, height, r, bpp);

	stbi_write_png(argv[2], width, height, CHANNEL_NUM, rgb_image_w, width * CHANNEL_NUM);

	stbi_image_free(rgb_image);

	return 0;
}
