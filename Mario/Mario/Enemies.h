#pragma once
#include <allegro5\allegro.h>

class Enemy
{
private:
	int ID;
	int x;
	int y;
	bool alive;
	int boundx;
	int boundy;

public:
	void CreateEnemies(Enemy guys[], int size, int counter);
	void SetEnemies(Enemy guys[], int size);
	void DrawEnemies(Enemy guys[], int size, int counter);
	void StartEnemies(Enemy guys[], int size);
	void Collision(Enemy guys[], int size, int counter);
	void Dead(Enemy guys[], int size);
	void Apocalypse(Enemy guys[], int size);


};