//-------------------------------------------------------------------------------------------------------------
// Main Solution
//-------------------------------------------------------------------------------------------------------------
/* 
   Includes:
            - Related Allegro Addon imports
			- Set constants for the frames/second (FPS) and frame height & width
			- Sets keys to be used (directional movement has been implemented, but the action key is unused)
			- Initialisations: allegro, keyboard, timer, event queue, image addon, bitmap, display
			- Initialisation ERROR checks are included
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------------------------------------
// Imports and Constants: Start
//-------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <stdio.h>
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_native_dialog.h" //importing the necessary allegro headers
#include <allegro5\allegro_font.h>				
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include "Objects.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

enum Keys { A, S, D, W, SPACE, L }; //Setting up needed keys for keyboard control of MC
int res_x = 1280; //constant integers that dictate the width & height of the display
int res_y = 820;
int pos_x = 0;
int checkpoint = 0;
int blockNum = 0;
const int num_proj = 5;
int level = 1;
int g = 1;


struct person {
	int r = 20;
	int feet = res_y - 55;
	int x = 200;
	int y = feet - (3 * r);
	int j_height = res_y - 450;
	int ms = 5;
	int jumpspeed = 7;
	int lives = 5;
	int score = 0;


}player;

int deathDelay = 0;
int c = 0;
int wait = 0;
int box_width = player.r * 2 + 15;
int box_bounds = box_width;
int pipe_width = 120;
int pipe_bounds = pipe_width;
int spike_height = 50;
int spike_width = 20;
bool deathPause = false;
bool LR = false;



void initproj(Projectiles proj[], int size);
void drawproj(Projectiles proj[], int size);
void shoot(Projectiles proj[], int size);
void update(Projectiles proj[], int size);
void SetEnemies(enemies guys[], int size);
void StartEnemies(enemies guys[], int size);
void CreateEnemies(enemies guys[], int size, int counter);
void DrawEnemies(enemies guys[], int size, int counter);
void Collision(Projectiles proj[], int sizeP, enemies guys[], int sizeE, int counter);
bool CollideEnemy(enemies guys[], int size, int counter);
void ISEEDEADPEOPLE(enemies guys[], int size);
void Apocalypse(enemies guys[], int size);

int num_bg = 10;
int num_ground = 10;

void GenerateSTART(bool check);

void HittingBlocks(Projectiles proj[], int size, int sizeB, block blocks[]);
void HittingPipes(Projectiles proj[], int size, int sizeP, Pipe pipes[]);

int const num_enemies = 22;
bool shot = false;

enemies guys[num_enemies];

// Audio Import Section
ALLEGRO_SAMPLE *shot1 = NULL;
ALLEGRO_SAMPLE_ID *foo = NULL;

ALLEGRO_SAMPLE *boom = NULL;
ALLEGRO_SAMPLE_ID *foo1 = NULL;

ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_ID *foo2 = NULL;

ALLEGRO_SAMPLE *jumping = NULL;
ALLEGRO_SAMPLE_ID *foo3 = NULL;

ALLEGRO_SAMPLE *bump = NULL;
ALLEGRO_SAMPLE_ID *foo4 = NULL;

ALLEGRO_SAMPLE *die = NULL;
ALLEGRO_SAMPLE_ID *foo5 = NULL;

ALLEGRO_SAMPLE *pause = NULL;
ALLEGRO_SAMPLE_ID *foo6 = NULL;

ALLEGRO_SAMPLE *GO = NULL;
ALLEGRO_SAMPLE_ID *foo7 = NULL;


ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;

// Audio Import Section End
//-------------------------------------------------------------------------------------------------------------
// Imports and Constants: End
//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
// Main Method: Start
//-------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{

//-------------------------------------------------------------------------------------------------------------
// NULL Pointers: Start
//-------------------------------------------------------------------------------------------------------------
	ALLEGRO_DISPLAY *display = NULL; //Creation of Null pointers
	ALLEGRO_EVENT_QUEUE *ev_q = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *MC = NULL;
//-------------------------------------------------------------------------------------------------------------
// NULL Pointers: End
//-------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
// Initialisations, certain Allegro creations and Error Checks: Start
//-------------------------------------------------------------------------------------------------------------

	if (!al_init()) //Checking if Allegro initialised correctly
	{
		fprintf(stderr, "Allegro failed initialisation \n");
		return -1;
	}

	if (!al_install_keyboard()) //Installing keyboard fucntionality
	{
		fprintf(stderr, "Keyboard initialisation failed\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS); //Game clock
	if (!timer)
	{
		fprintf(stderr, "Failed to create timer \n");
		return -1;
	}

	if (!al_init_image_addon()) // For the Main character bitmap and others to come
	{
		al_show_native_message_box(display, "ERROR", "ERROR", "Failed to initialise image addon",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	display = al_create_display(widthS, heightS); //Creating the display
	if (!display)
	{
		fprintf(stderr, "Display failed \n");
		return -1;
	}

	MC = al_create_bitmap(32, 32);//Values are arbitrary, need to scale the sprite itself
	if (!MC)
	{
		fprintf(stderr, "Failed to creat Main Character \n");
		al_destroy_display(display); //Deallocation of memory
		al_destroy_timer(timer);
		return -1;
	}

	MC = al_load_bitmap("MC.png"); //Loading the Main Character sprite, currently one image of temp sprite
	if (!MC)
	{
		fprintf(stderr, "Failed to load image \n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_draw_bitmap(MC, 32, 32, NULL); //Draws the Main Character to the display

	ev_q = al_create_event_queue(); //Creation of event queue
	if (!ev_q)
	{
		fprintf(stderr, "Failed to create event queue \n");
		al_destroy_bitmap(MC);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	//-------------------------------------------------------------------------------------------------------------
	// Initialisation, certain Allegro creations and ERROR checks: End
	//-------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------
	//            Main Character Section
	//--------------------------------------------------
	float posX = widthS - 800; //Starting position
	float posY = heightS - 100;
	bool keyState[4] = { false, false, false, false }; //key press states for button press implementation
	bool redraw = true;
	bool doexit = false; //For exit logic
	//--------------------------------------------------
    //            Main Character Section: temp. end
	//--------------------------------------------------
	
	//-------------------------------------------------------------------------------------------------------------
	// Event Source Registration: Start
	//-------------------------------------------------------------------------------------------------------------
	al_register_event_source(ev_q, al_get_display_event_source(display));
	al_register_event_source(ev_q, al_get_timer_event_source(timer));
	al_register_event_source(ev_q, al_get_keyboard_event_source());
	//-------------------------------------------------------------------------------------------------------------
	// Event Source Registration: End
	//------------------------------------------------------------------------------------------------------------
	
	//From previous iteration, don't remove for now
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	//al_flip_display(); //Using the dual buffer method, splashTest was drawn on "back" buffer

	//-------------------------------------------------------------------------------------------------------------
	// Main Game Loop: Start
	//-------------------------------------------------------------------------------------------------------------
	al_start_timer(timer);
	while (!doexit) //While escape key isn't pressed
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(ev_q, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) //Checks sources
		{
			//--------------------------------------------------
			//            Main Character Section: cont.
			//--------------------------------------------------
			if (keyState[key_UP] && posY >= 4.0) //Dictates movement, arbitrary values for now
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
			//--------------------------------------------------
			//            Main Character Section: temp. end
			//--------------------------------------------------
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { break; }

		//--------------------------------------------------
		//            Main Character Section: cont.
		//--------------------------------------------------
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
				doexit = true; //Exit logic
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
	    //--------------------------------------------------
	    //            Main Character Section: End
	    //--------------------------------------------------
	
//-------------------------------------------------------------------------------------------------------------
// Memory Deallocation: Start
//-------------------------------------------------------------------------------------------------------------
	al_destroy_bitmap(MC);
	al_destroy_timer(timer);
	al_destroy_display(display); //deallocating memory from the display and image bitmap
	al_destroy_event_queue(ev_q);
//-------------------------------------------------------------------------------------------------------------
// Memory Deallocation: End
//-------------------------------------------------------------------------------------------------------------
	return 0;
}

//-------------------------------------------------------------------------------------------------------------
// Main Method: End
//-------------------------------------------------------------------------------------------------------------

//aadd