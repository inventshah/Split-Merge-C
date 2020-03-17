// Sachin Shah
// March 16, 2020

#include "splitmerge.h"
#include "block.h"
#include "image.h"
#include "node.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

uint8_t random_255(void)
{
	return rand() % 256;
}

void colorize(Image *img, Node *node)
{
	uint32_t x, y, upper_x, upper_y;

	if (node->top_left == NULL)
	{
		upper_x = node->x + node->width;
		upper_y = node->y + node->height;

		for (x = node->x; x <= upper_x; x++)
		{
			for (y = node->y; y <= upper_y; y++)
			{
				set_rgb(img, x, y, node->red, node->green, node->blue);
			}
		}
	}
	else
	{
		colorize(img, node->top_left);
		colorize(img, node->top_right);
		colorize(img, node->bottom_left);
		colorize(img, node->bottom_right);
	}
}


void segment(Image *img, uint32_t tolerance)
{
	Node *root = create_tree(tolerance, img);

	colorize(img, root);

	free_nodes(root);
}