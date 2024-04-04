#include <stdio.h>
#include <inttypes.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define XCOORD 0
#define YCOORD 0

//typedef struct {
//	uint8_t r;
//	uint8_t g;
//	uint8_t b;
//} Pixel;

void printRBG(unsigned long pixel)
{
	unsigned char r, g, b;
	b = pixel;
	g = pixel >> 8;
	r = pixel >> 16;
	fprintf(stdout, "%d %d %d\n", r, g, b);
}


int main(void) 
{
	Display *display;
	if ((display = XOpenDisplay(NULL)) == NULL) 
	{
		fprintf(stderr, "Unable to open display.\n");
		printRBG(0);
		return 1;
	}

	Window root = DefaultRootWindow(display);
	XImage *image;
	if ((image = XGetImage(display, root, XCOORD, YCOORD, 1, 1, AllPlanes, ZPixmap)) == NULL)
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
