
//Need to append image to bitmap of MC

#include <iostream>
#include <stdio.h>
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h" //importing the necessary allegro headers

const float FPS = 60; //necessary for game clock and draw rate
const int widthS = 800;
const int heightS = 600; //constant integers that dictate the width and height of the display
enum c_keys 
{
	key_UP, key_DOWN, key_RIGHT, key_LEFT, key_ACT //Setting up needed keys for keyboard control of MC
};

int main(int argc, char** argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	//ALLEGRO_BITMAP *image = NULL; //Creation of the NULL pointers to be used
	ALLEGRO_EVENT_QUEUE *ev_q = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *MC = NULL;

	if (!al_init()) //Checking if Allegro initialised correctly
	{
		fprintf(stderr, "Allegro failed initialisation \n");
		return -1;
	}

	//--------------------------------------------------
	//            Main Character Section
	//--------------------------------------------------
	//--------------------------------------------------
	float posX = widthS / 2.0 - 16;
	float posY = heightS / 2.0 - 16;
	bool keyState[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	if (!al_install_keyboard())
	{
		fprintf(stderr, "Keyboard initialisation failed\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		fprintf(stderr, "Failed to create timer \n");
		return -1;
	}

	
	//--------------------------------------------------

	

	//if (!al_init_image_addon())
	//{
	//al_show_native_message_box(display, "ERROR", "ERROR", "Failed to initialise image addon",
	//NULL, ALLEGRO_MESSAGEBOX_ERROR);
	//return 0;
	//}

	display = al_create_display(widthS, heightS); //Creating the display
	if (!display)
	{
		fprintf(stderr, "Display failed \n");
		return -1;
	}
	// MC Stuff
	/*MC = al_create_bitmap(32, 32);
	if (!MC)
	{
		fprintf(stderr, "Failed to creat Main Character \n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_target_bitmap(MC);
	al_clear_to_color(al_map_rgb(255, 0 ,255));
	al_set_target_bitmap(al_get_backbuffer(display));
	*/
	MC = al_load_bitmap("MC.png");
	if (!MC)
	{
		fprintf(stderr, "Failed to load image \n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_draw_bitmap(MC, 100, 100, NULL);

	ev_q = al_create_event_queue();
	if (!ev_q)
	{
		fprintf(stderr, "Failed to create event queue \n");
		al_destroy_bitmap(MC);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(ev_q, al_get_display_event_source(display));
	al_register_event_source(ev_q, al_get_timer_event_source(timer));
	al_register_event_source(ev_q, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	// MC Stuff

	//image = al_load_bitmap("splashTest.png"); //Loading the splashTest image into the Bitmap pointer
	
//	if (!image)
	//{
	//	al_show_native_message_box(display, "ERROR", "ERROR", "Failed to load image",
	//	NULL, ALLEGRO_MESSAGEBOX_ERROR);
	//	al_destroy_display(display);
	//	return 0;
	//}
	
//	al_draw_bitmap(image, 200, 200, 0); //Drawing the bitmap onto the display with corresponding sizes

	al_flip_display(); //Using the dual buffer method, splashTest was drawn on "back" buffer

	// MC STUFF
	al_start_timer(timer);
	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(ev_q, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (keyState[key_UP] && posY >= 4.0)
			{
				posY -= 4.0;
			}
			if (keyState[key_DOWN] && posY <= heightS - 28)
			{
				posY += 4.0;
			}
			if (keyState[key_LEFT] && posX >= 4.0)
			{
				posX -= 4.0;
			}
			if (keyState[key_RIGHT] && posX <= widthS - 28)
			{
				posX += 4.0;
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { break; }
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keyState[key_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keyState[key_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keyState[key_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keyState[key_RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keyState[key_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keyState[key_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keyState[key_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keyState[key_RIGHT] = false;
				break;
			case  ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(ev_q))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_bitmap(MC, posX, posY, 0);
			al_flip_display();
		}
	}
	// MC STUFF
	//al_rest(3.0);
	al_destroy_bitmap(MC);
	al_destroy_timer(timer);
	al_destroy_display(display); //deallocating memory from the display and image bitmap
	al_destroy_event_queue(ev_q);
	//al_destroy_bitmap(image);
	return 0;
}