#include "MChar.h"

MChar::MChar(void)
{

}

MChar::~MChar()
{
	
}

void MChar::load()
{
	posX = 0.0;
	posY = 0.0;
	MCimage = al_load_bitmap("MCimage.png");
}

void MChar::unload()
{
	al_destroy_bitmap(MCimage);
}

void MChar::update(ALLEGRO_EVENT ev)
{
	
}

void MChar::draw(ALLEGRO_DISPLAY *display)
{
	al_draw_bitmap(MCimage, posX, posY, NULL);
}