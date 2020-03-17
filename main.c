// Sachin Shah
// March 12, 2020

#include "image.h"
#include "utils.h"
#include "splitmerge.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	Image *img = open_image("source.png");

	segment(img, 100);

	save_image(img, "test.png");

	img = free_image(img);

	return 0;
}