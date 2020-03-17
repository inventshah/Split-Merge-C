// Sachin Shah
// March 12, 2020

#include "image.h"
#include "utils.h"
#include "splitmerge.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	Image *img = NULL;
	char *source, *save;
	uint32_t tolerance;

	if (argc < 4) error("Too few command line arguments. Need [source filename] [output filename] [tolerance].");

	img = open_image(argv[1]);
	tolerance = atoi(argv[3]);

	segment(img, tolerance);
	save_image(img, argv[2]);

	img = free_image(img);

	return 0;
}