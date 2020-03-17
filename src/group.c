// Sachin Shah
// March 17, 2020

#include "image.h"
#include "group.h"
#include "utils.h"

#include <png.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Element *add_element(Node *node, Element *last)
{
	Element *ptr = (Element *) calloc(1, sizeof(Element));
	check_null(ptr, "calloc failed to find space for an Element");

	ptr->x = node->x;
	ptr->y = node->y;
	ptr->width = node->width;
	ptr->height = node->height;
	ptr->red = node->red;
	ptr->green = node->green;
	ptr->blue = node->blue;
	ptr->next = NULL;

	if (last != NULL) last->next = ptr;

	return ptr;
}

Element *tree_to_list(Element *first, Node *root)
{
	Element *last = first;

	if (root->top_left == NULL)
	{
		if (first == NULL)
		{
			first = add_element(root, NULL);
			return first;
		}

		while (last != NULL && last->next != NULL) last = last->next;
		add_element(root, last);
	}
	else
	{
		first = tree_to_list(first, root->top_left);
		first = tree_to_list(first, root->top_right);
		first = tree_to_list(first, root->bottom_left);
		first = tree_to_list(first, root->bottom_right);
	}

	return first;
}

int8_t touching(Element *one, Element *two)
{
	if (one->y == two->y || one->y == two->height + two->y)
	{
		return ((one->x >= two->x && one->x <= two->x + two->width) || (two->x >= one->x && two->x <= one->x + one->width));
	}
	if (one->x == two->x || one->x == two->width + two->x)
	{
		return ((one->y >= two->y && one->y <= two->y + two->height) || (two->y >= one->y && two->y <= one->y + one->height));
	}

	return 0;
}

uint32_t element_distance(Element *element, Group *group)
{
	Element *current = group->root;
	int32_t rdiff, gdiff, bdiff;

	rdiff = element->red - group->red;
	gdiff = element->green - group->green;
	bdiff = element->blue - group->blue;

	rdiff *= rdiff;
	gdiff *= gdiff;
	bdiff *= bdiff;

	while (current != NULL)
	{
		if (touching(current, element) || touching(element, current)) break;
		current = current->next;
	}

	if (current == NULL) return MAX_DIST;

	return sqrt(rdiff + gdiff + bdiff);
}

Group *add_group(Group *last, Element *node)
{
	Group *ptr = (Group *) calloc(1, sizeof(Group));
	check_null(ptr, "calloc failed to find space for a Group");

	ptr->red = node->red;
	ptr->green = node->green;
	ptr->blue = node->blue;
	ptr->count = node->width * node->height;
	if (ptr->count == 0) ptr->count = 1;
	ptr->root = node;
	node->next = NULL;
	ptr->next = NULL;

	if (last != NULL) last->next = ptr;

	return ptr;
}

void add_element_to_group(Group *group, Element *node)
{
	Element *last = group->root;
	uint32_t count = node->width * node->height;

	while (last->next != NULL) last = last->next;

	last->next = node;
	node->next = NULL;

	group->red *= group->count;
	group->green *= group->count;
	group->blue *= group->count;

	group->red += (node->red * count);
	group->green += (node->green * count);
	group->blue += (node->blue * count);

	group->count += count;
	group->red /= group->count;
	group->green /= group->count;
	group->blue /= group->count;
}

Group *create_groups(Element *root, uint32_t tolerance)
{
	Element *current_element = root->next, *next_element;
	Group *first_group, *last_group, *current_group = NULL;
	first_group = last_group = add_group(NULL, root);

	while (current_element != NULL)
	{
		current_group = first_group;

		while (current_group != NULL)
		{
			if (element_distance(current_element, current_group) < tolerance) break;
			current_group = current_group->next;
		}

		next_element = current_element->next;
		if (current_group == NULL)
		{
			last_group = add_group(last_group, current_element);
		}
		else
		{
			add_element_to_group(current_group, current_element);
		}

		current_element = next_element;
	}

	return first_group;
}

void free_elements(Element *element)
{
	if (element != NULL)
	{
		free_elements(element->next);
		free(element);
	}
}

void free_groups(Group *group)
{
	if (group != NULL)
	{
		free_groups(group->next);
		free_elements(group->root);
		free(group);
	}
}
