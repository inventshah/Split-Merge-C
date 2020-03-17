// Sachin Shah
// March 16, 2020
// Split and merge methods

#ifndef _SPLITMERGE_H
#define _SPLITMERGE_H

#define MAX_DIST 765
#define MIN_DIST 0

#include "block.h"

#include <png.h>
#include <stdint.h>

uint32_t distance(png_bytep rgb);
int8_t is_homogeneous(Block *block, uint32_t tolerance, Image *img);

uint8_t random_255(void);

void segment(Image *img, uint32_t tolerance);

#endif