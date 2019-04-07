#include <stdint.h>

#ifndef __INCLUDE_BLUR_H__
#define __INCLUDE_BLUR_H__

void fast_gauss_blur(uint8_t *scl, uint8_t *tcl, int width, int height, int radius, int bpp);

#endif
