#include<allegro5\allegro.h>
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_primitives.h>


const int width = 800;
const int height = 600;

struct Background
{
	float x, y, velX, velY;
	int dirX, dirY, w, h;

	ALLEGRO_BITMAP *image;
};

void InitBackground(Background &back, float x, float y, float velx, float vely, int w, int h, int dirx, int diry, ALLEGRO_BITMAP *image);
void UptadeBackground(Background &back);
void DrawBackground(Background &back);
int main()
{
	//Varables
	bool done = false;
	bool render = false;
	Background BG;

	//allegro initialisers
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_que = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *bgImage;

	//initialise program
	if (!al_init())
		return -1;

	display = al_create_display(width, height);

	if (!display)
		return -1;


	//addons
	al_install_keyboard();
	al_init_image_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	bgImage = al_load_bitmap("back2.png");

	InitBackground(BG, 0, 0, 1, 0, width, height, -1, 1, bgImage);


	event_que = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_que, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:

				break;
			case ALLEGRO_KEY_RIGHT:

				break;
			case ALLEGRO_KEY_UP:

				break;

			case ALLEGRO_KEY_DOWN:

				break;
			}
		}
		else if (ev.type = ALLEGRO_EVENT_TIMER)
		{
			UptadeBackground(BG);
			render = true;
		}
		if (render && al_is_event_queue_empty(event_que))
		{
			render = false;


			DrawBackground(BG);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));

		}
	}
	al_rest(5.0);
	al_destroy_bitmap(bgImage);
	al_destroy_event_queue(event_que);
	al_destroy_display(display);


	return 0;
}

void InitBackground(Background &back, float x, float y, float velx, float vely, int w, int h, int dirx, int diry, ALLEGRO_BITMAP *image)
{
	back.x = x;
	back.y = y;
	back.velX = velx;
	back.velY = vely;
	back.w = w;
	back.h = h;
	back.dirX = dirx;
	back.dirY = diry;
	back.image = image;


};

void UptadeBackground(Background &back)
{
	back.x += back.velX * back.dirX;
	if (back.x + back.w <= 0)
		back.x = 0;
};

void DrawBackground(Background &back)
{
	al_draw_bitmap(back.image, back.x, back.y, 0);
};
