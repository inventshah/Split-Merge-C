// Sachin Shah
// March 16, 2020
// Merge list

#ifndef _GROUP_H
#define _GROUP_H

#include "image.h"
#include "node.h"

#include <png.h>
#include <stdint.h>

struct element
{
	uint32_t x;
	uint32_t y;
	uint32_t width;
	uint32_t height;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	struct element *next;
};

typedef struct element Element;

struct group
{
	uint32_t red;
	uint32_t green;
	uint32_t blue;
	uint32_t count;
	Element *root;
	struct group *next;
};

typedef struct group Group;

Element *add_element(Node *node, Element *last);
Element *tree_to_list(Element *first, Node *root);

uint32_t element_distance(Element *element, Group *group);

Group *add_group(Group *last, Element *node);
Group *create_groups(Element *root, uint32_t tolerance);

void free_elements(Element *elm);
void free_groups(Group *group);


#endif