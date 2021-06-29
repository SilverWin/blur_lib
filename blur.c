#include <blur.h>

#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)

static void boxes_for_gauss(int sigma, int sizes[3])
{
	double wIdeal;
	int wl;
	int wu;
	double mIdeal;
	int m;
	int n = 3;

	wIdeal = sqrt((double)(12 * sigma * sigma / n) + 1); /* Ideal averaging filter width */
	wl = (int)floor(wIdeal);
	if (wl % 2 == 0)
		wl--;
	wu = wl + 2;

	mIdeal = (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4);
	m = (int)round(mIdeal);

	for (int i = 0; i < n; i++)
	{
		if (i < m)
		{
			sizes[i] = wl;
		}
		else
		{
			sizes[i] = wu;
		}
	}
}

static void box_blur_H(uint8_t *scl, uint8_t *tcl, int w, int h, int r, int bpp)
{
	for (int i = 0; i < h; i++)
	{
		for (int k = 0; k < bpp; k++)
		{
			int ti = i * w * bpp + k;
			int li = ti;
			int ri = ti + r * bpp;
			int fv = scl[li];
			int lv = scl[ti + (w - 1) * bpp];
			int val = (r + 1) * fv;
			for (int j = 0; j < r; j++)
			{
				val += scl[ti + (j * bpp)];
			}
			for (int j = 0; j <= r; j++)
			{
				val += scl[ri] - fv;
				tcl[ti] = (uint8_t)round(val / (r + r + 1));
				ri += bpp;
				ti += bpp;
			}
			for (int j = r + 1; j < (w - r); j++)
			{
				val += scl[ri] - scl[li];
				tcl[ti] = (uint8_t)round(val / (r + r + 1));
				li += bpp;
				ri += bpp;
				ti += bpp;
			}
			for (int j = w - r; j < w; j++)
			{
				val += lv - scl[li];
				tcl[ti] = (uint8_t)round(val / (r + r + 1));
				li += bpp;
				ti += bpp;
			}
		}
	}
}

static void box_blur_T(uint8_t *scl, uint8_t *tcl, int w, int h, int r, int bpp)
{
	for (int i = 0; i < w; i++)
	{
		for (int k = 0; k < bpp; k++)
		{
			int ti = i * bpp + k;
			int li = ti;
			int ri = ti + r * w * bpp;
			int fv = scl[ti];
			int lv = scl[ti + w * (h - 1) * bpp];
			int val = (r + 1) * fv;
			for (int j = 0; j < r; j++)
			{
				val += scl[ti + j * w * bpp];
			}
			for (int j = 0; j <= r; j++)
			{
				val += scl[ri] - fv;
				tcl[ti] = (uint8_t)round(val / (r + r + 1));
				ri += w * bpp;
				ti += w * bpp;
			}
			for (int j = r + 1; j < (h - r); j++)
			{
				val += scl[ri] - scl[li];
				tcl[ti] = (uint8_t)round(val / (r + r + 1));
				li += w * bpp;
				ri += w * bpp;
				ti += w * bpp;
			}
			for (int j = h - r; j < h; j++)
			{
				val += lv - scl[li];
				tcl[ti] = (uint8_t)round(val / (r + r + 1));
				li += w * bpp;
				ti += w * bpp;
			}
		}
	}
}

static void box_blur(uint8_t *scl, uint8_t *tcl, int w, int h, int r, int bpp)
{
	for (int i = 0; i < (h * w * bpp); i++)
	{
		tcl[i] = scl[i];
	}
	box_blur_H(tcl, scl, w, h, r, bpp);
	box_blur_T(scl, tcl, w, h, r, bpp);
}

void fast_gauss_blur(uint8_t *scl, uint8_t *tcl, int w, int h, int r, int bpp)
{
	int bxs[3];
	boxes_for_gauss(r, bxs);
	box_blur(scl, tcl, w, h, (bxs[0] - 1) / 2, bpp);
	box_blur(tcl, scl, w, h, (bxs[1] - 1) / 2, bpp);
	box_blur(scl, tcl, w, h, (bxs[2] - 1) / 2, bpp);
}
