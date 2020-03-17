// Sachin Shah
// March 16, 2020
// Split and merge methods

#ifndef _SPLITMERGE_H
#define _SPLITMERGE_H

#include "node.h"

#include <png.h>
#include <stdint.h>

uint8_t random_255(void);

void colorize(Image *img, Node *node);
void segment(Image *img, uint32_t tolerance);

#endif