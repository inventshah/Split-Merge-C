// Sachin Shah
// March 16, 2020

#include "splitmerge.h"
#include "block.h"
#include "image.h"
#include "node.h"
#include "group.h"

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

void colorize_2(Image *img, Group *group)
{
	uint32_t x, y, upper_x, upper_y;

	Element *element = group->root;

	uint8_t red, green, blue;
	red = random_255();
	green = random_255();
	blue = random_255();

	while (element != NULL)
	{
		upper_x = element->x + element->width;
		upper_y = element->y + element->height;

		for (x = element->x; x <= upper_x; x++)
		{
			for (y = element->y; y <= upper_y; y++)
			{
				//set_rgb(img, x, y, red, green, blue);
				set_rgb(img, x, y, group->red, group->green, group->blue);
			}
		}

		element = element->next;
	}
}

void merge(Image *img, Node *tree, uint32_t tolerance)
{
	Element *list = tree_to_list(NULL, tree), *temp;

	Group *groups = create_groups(list, tolerance), *current_group = NULL;

	current_group = groups;
	while (current_group != NULL)
	{
		colorize_2(img, current_group);
		current_group = current_group->next; 
	}

	free_groups(groups);
}

void segment(Image *img, uint32_t tolerance)
{
	printf("Splititng\n");
	Node *root = create_tree(tolerance, img);

	colorize(img, root);
	printf("Merging\n");
	merge(img, root, tolerance);

	free_nodes(root);
}