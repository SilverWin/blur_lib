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
	char* input  = argv[1];
	char* output = argv[2];

	if (input == NULL) input = "in.png";
	if (output == NULL) output = "out.png";

	uint8_t *rgb_image = stbi_load(input, &width, &height, &bpp, STBI_rgb);
	if (rgb_image == NULL) {
		printf("Cannot open input PNG file: %s reason: %s\n", input, stbi_failure_reason());
		exit(1);
	}

	uint8_t *rgb_image_w;
	rgb_image_w = malloc((size_t)width * height * CHANNEL_NUM);

	fast_gauss_blur(rgb_image, rgb_image_w, width, height, r, bpp);

	stbi_write_png(output, width, height, CHANNEL_NUM, rgb_image_w, width * CHANNEL_NUM);

	stbi_image_free(rgb_image);

	return 0;
}
