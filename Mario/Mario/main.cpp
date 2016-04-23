
#include <iostream>
#include <stdio.h>
#include "allegro5\allegro5.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h"

const int widthS = 800;
const int heightS = 600;

int main(int argc, char** argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *image = NULL;
	if (!al_init())
	{
		fprintf(stderr, "Allegro failed initialisation \n");
		return -1;
	}

	if (!al_init_image_addon())
	{
		al_show_native_message_box(display, "ERROR", "ERROR", "Failed to initialise image addon",
		NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	display = al_create_display(widthS, heightS);
	if (!al_create_display(widthS, heightS))
	{
		fprintf(stderr, "Display failed \n");
		return -1;
	}

	image = al_load_bitmap("splashTest.png");
	
	if (!image)
	{
		al_show_native_message_box(display, "ERROR", "ERROR", "Failed to load image",
		NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return 0;
	}
	
	al_draw_bitmap(image, 200, 200, 0);

	al_flip_display();
	al_rest(3.0);
	al_destroy_display(display);
	al_destroy_bitmap(image);
	return 0;
}