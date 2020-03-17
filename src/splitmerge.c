// Sachin Shah
// March 16, 2020

#include "splitmerge.h"
#include "block.h"
#include "image.h"

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

uint32_t distance(png_bytep rgb)
{
	uint32_t r = rgb[0], g = rgb[1], b = rgb[2];

	r *= r;
	g *= g;
	b *= b;

	return sqrt(r + g + b);
}

int8_t is_homogeneous(Block *block, uint32_t tolerance, Image *img)
{
	uint32_t x, y, upper_x, upper_y;
	uint32_t min_distance = MAX_DIST, max_distance = MIN_DIST, current_distance;
	png_bytep rgb = NULL;

	if (block->width == 0 || block->height == 0) return HOMOGENEOUS;

	upper_x = block->x + block->width;
	upper_y = block->y + block->height;

	for (x = block->x; x < upper_x; x++)
	{
		for (y = block->y; y < upper_y; y++)
		{
			rgb = get_rgb(img, x, y);
			current_distance = distance(rgb);

			if (min_distance > current_distance) min_distance = current_distance;
			if (max_distance < current_distance) max_distance = current_distance;
		}
	}

	return max_distance - min_distance < tolerance ? HOMOGENEOUS : 0;
}

uint8_t random_255(void)
{
	return rand() % 256;
}

void segment(Image *img, uint32_t tolerance)
{
	Block *first_block = NULL, *last_block = NULL, *current_block, *temp;
	uint32_t x, y, upper_x, upper_y;
	uint8_t red, green, blue;

	current_block = first_block = last_block = add_block(NULL, 0, 0, img->width, img->height);

	srand(time(NULL));

	printf("segmenting\n");
	uint32_t num = 0;
	while (current_block != NULL)
	{
		if (is_homogeneous(current_block, tolerance, img) == 0)
		{
			last_block = split_block(current_block, last_block);
			if (current_block == first_block) first_block = current_block->next;

			if (current_block->previous != NULL) current_block->previous->next = current_block->next;
			if (current_block->next != NULL) current_block->next->previous = current_block->previous;

			temp = current_block->next;
			free(current_block);
			current_block = temp;
		}
		else
		{
			current_block = current_block->next;
		}

		
		num++;
	}

	current_block = first_block;

	printf("colorizing %u splits\n", num);
	while (current_block != NULL)
	{
		red = random_255();
		green = random_255();
		blue = random_255();

		upper_x = current_block->x + current_block->width;
		upper_y = current_block->y + current_block->height;

		for (x = current_block->x; x <= upper_x; x++)
		{
			for (y = current_block->y; y <= upper_y; y++)
			{
				set_rgb(img, x, y, red, green, blue);
			}
		}
		current_block = current_block->next;
	}

	free_blocks(first_block);
}
