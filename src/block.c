// Sachin Shah
// March 16, 2020
// Split and merge methods

#include "block.h"
#include "image.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>

Block *split_block(Block *block, Block *last)
{
	uint32_t half_width, half_height;

	half_width = block->width / 2;
	half_height = block->height / 2;

	last = add_block(last, block->x             , block->y              , half_width, half_height);

	last = add_block(last, block->x + half_width, block->y              , half_width, half_height);
	last = add_block(last, block->x             , block->y + half_height, half_width, half_height);

	last = add_block(last, block->x + half_width, block->y + half_height, half_width, half_height);

	return last;
}

Block *add_block(Block *last, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	Block *ptr = (Block *) malloc(sizeof(Block));
	check_null(ptr, "malloc failed to find space for a Block");

	ptr->x = x;
	ptr->y = y;
	ptr->width = width;
	ptr->height = height;
	ptr->red = 0;
	ptr->green = 0;
	ptr->blue = 0;
	ptr->previous = last;
	ptr->next = NULL;

	if (last != NULL) last->next = ptr;
	return ptr;
}

void free_blocks(Block *root)
{
	if (root != NULL)
	{
		free_blocks(root->next);
		free(root);
	}
}