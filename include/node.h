// Sachin Shah
// March 16, 2020
// Split tree

#ifndef _NODE_H
#define _NODE_H

#include "image.h"

#include <png.h>
#include <stdint.h>

#define HOMOGENEOUS 1
#define NOT_HOMOGENEOUS 0

#define MAX_DIST 765
#define MIN_DIST 0

struct node
{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint32_t group;
	struct node *parent;
	struct node *top_left;
	struct node *bottom_left;
	struct node *top_right;
	struct node *bottom_right;
};

typedef struct node Node;

Node *create_tree(uint32_t tolerance, Image *img);

void split_node(Node *node, uint32_t tolerance, Image *img);
Node *add_node(Node *parent, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t tolerance, Image *img);

uint32_t node_distance(Node *one, Node *two);
uint32_t rgb_distance(png_bytep rgb);

int8_t is_node_homogeneous(Node *node, uint32_t tolerance, Image *img);

void free_nodes(Node *root);

#endif