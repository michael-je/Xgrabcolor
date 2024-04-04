#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define USAGE "Usage: grabcolor <x coordinate> <y coordinate>\n"
#define DISPLAY 0


void printRBG(unsigned long pixel)
{
	unsigned char r, g, b;
	b = pixel;
	g = pixel >> 8;
	r = pixel >> 16;
	fprintf(stdout, "%d %d %d\n", r, g, b);
}


int main(int argc, char *argv[]) 
{
	if (argc != 3)
	{
		printf(USAGE);
		return 1;
	}
	long x, y;
	x = strtol(argv[1], NULL, 10);
	y = strtol(argv[2], NULL, 10);

	Display *display;
	if ((display = XOpenDisplay(DISPLAY)) == NULL) 
	{
		fprintf(stderr, "Unable to open display.\n");
		printRBG(0);
		return 1;
	}
	int dispmaxx, dispmaxy;
	dispmaxx = XDisplayWidth(display, DISPLAY);
	dispmaxy = XDisplayHeight(display, DISPLAY);
	if (
		x < 0 || x >= dispmaxx ||
		y < 0 || y >= dispmaxy
	) {
		fprintf(
			stderr, 
			"Pixel value out of bounds: 0 <= x <= %d, 0 <= y <= %d\n", 
			dispmaxx - 1, dispmaxy - 1
		);
		printRBG(0);
		return 1;
	}

	Window root = DefaultRootWindow(display);
	XImage *image;
	if ((image = XGetImage(display, root, x, y, 1, 1, AllPlanes, ZPixmap)) == NULL)
	{
		fprintf(stderr, "Unable to capture image.\n");
		printRBG(0);
		return 1;
	}

	unsigned long pixel = XGetPixel(image, 0, 0);
	printRBG(pixel);

	XDestroyImage(image);
	XCloseDisplay(display);
	return 0;
}
