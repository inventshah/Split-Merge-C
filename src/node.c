// Sachin Shah
// March 16, 2020

#include "node.h"
#include "image.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Node *create_tree(uint32_t tolerance, Image *img)
{
	Node *ptr = (Node *) calloc(1, sizeof(Node));
	check_null(ptr, "calloc failed to find space for the root Node");

	ptr->x = 0;
	ptr->y = 0;
	ptr->width = img->width;
	ptr->height = img->height;

	split_node(ptr, tolerance, img);

	return ptr;
}

uint32_t node_distance(Node *one, Node *two)
{
	int32_t rdiff, gdiff, bdiff;

	rdiff = one->red - two->red;
	gdiff = one->green - two->green;
	bdiff = one->blue - two->blue;

	rdiff *= rdiff;
	gdiff *= gdiff;
	bdiff *= bdiff;

	return sqrt(rdiff + gdiff + bdiff);
}

void split_node(Node *node, uint32_t tolerance, Image *img)
{
	uint32_t half_width, half_height;

	half_width = node->width / 2;
	half_height = node->height / 2;

	node->top_left     = add_node(node, node->x             , node->y              , half_width, half_height, tolerance, img);
	node->top_right    = add_node(node, node->x + half_width, node->y              , half_width, half_height, tolerance, img);
	node->bottom_left  = add_node(node, node->x             , node->y + half_height, half_width, half_height, tolerance, img);
	node->bottom_right = add_node(node, node->x + half_width, node->y + half_height, half_width, half_height, tolerance, img);
}

Node *add_node(Node *parent, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t tolerance, Image *img)
{
	Node *ptr = (Node *) calloc(1, sizeof(Node));
	check_null(ptr, "calloc failed to find space for a Node");

	ptr->x = x;
	ptr->y = y;
	ptr->width = width;
	ptr->height = height;
	ptr->parent = parent;

	if (is_node_homogeneous(ptr, tolerance, img) == NOT_HOMOGENEOUS)
	{
		split_node(ptr, tolerance, img);
	}

	return ptr;
}

uint32_t rgb_distance(png_bytep rgb)
{
	uint32_t r = rgb[0], g = rgb[1], b = rgb[2];

	r *= r;
	g *= g;
	b *= b;

	return sqrt(r + g + b);
}

int8_t is_node_homogeneous(Node *node, uint32_t tolerance, Image *img)
{
	uint32_t x, y, upper_x, upper_y;
	uint32_t min_distance = MAX_DIST, max_distance = MIN_DIST, current_distance;
	uint32_t red = 0, green = 0, blue = 0, count = 0;
	png_bytep rgb = NULL;

	if (node->width == 0 || node->height == 0) return HOMOGENEOUS;

	upper_x = node->x + node->width;
	upper_y = node->y + node->height;

	for (x = node->x; x < upper_x; x++)
	{
		for (y = node->y; y < upper_y; y++)
		{
			rgb = get_rgb(img, x, y);
			current_distance = rgb_distance(rgb);

			red += rgb[0];
			green += rgb[1];
			blue += rgb[2];

			if (min_distance > current_distance) min_distance = current_distance;
			if (max_distance < current_distance) max_distance = current_distance;

			count++;
		}
	}

	node->red = red / count;
	node->green = green / count;
	node->blue = blue / count;

	return max_distance - min_distance < tolerance ? HOMOGENEOUS : NOT_HOMOGENEOUS;
}

void free_nodes(Node *root)
{
	if (root != NULL)
	{
		free_nodes(root->top_right);
		free_nodes(root->top_left);
		free_nodes(root->bottom_right);
		free_nodes(root->bottom_left);
		free(root);
	}
}
