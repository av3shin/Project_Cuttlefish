#pragma once
#include <allegro5\allegro.h>
class MChar
{

private:
	ALLEGRO_BITMAP *MCimage;
	float posX, posY, movSpeed;

public:
	MChar(void);
	~MChar(void);

	void load();
	void unload();
	void update(ALLEGRO_EVENT ev);
	void draw(ALLEGRO_DISPLAY *display);
};