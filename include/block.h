// Sachin Shah
// March 16, 2020
// Split and merge methods

#ifndef _BLOCK_H
#define _BLOCK_H

#include "image.h"

#include <stdint.h>

#define HOMOGENEOUS 1

struct block
{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	struct block *previous;
	struct block *next;
};

typedef struct block Block;

Block *split_block(Block *block, Block *last);
Block *add_block(Block *root, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

void free_blocks(Block *root);

#endif