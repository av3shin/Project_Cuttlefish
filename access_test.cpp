#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

int main()
{
	al_init();
	al_init_font_addon();
	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	ALLEGRO_FONT* font_type = al_create_builtin_font();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font_type, al_map_rgb(255, 20, 23), 400, 300, ALLEGRO_ALIGN_CENTER, "Sherwin Moodley");
	al_draw_text(font_type, al_map_rgb(255, 20, 23), 400, 320, ALLEGRO_ALIGN_CENTER, "213538912");
	al_draw_text(font_type, al_map_rgb(255, 20, 23), 400, 340, ALLEGRO_ALIGN_CENTER, "Group 3");
	al_flip_display();
	al_rest(4.0);

	return 0;
}