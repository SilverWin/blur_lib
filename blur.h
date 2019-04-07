#include <stdint.h>

#ifndef __INCLUDE_BLUR_H__
#define __INCLUDE_BLUR_H__

void gaussBlur_4(uint8_t* scl, uint8_t* tcl, int w, int h, int r, int bpp);

#endif

