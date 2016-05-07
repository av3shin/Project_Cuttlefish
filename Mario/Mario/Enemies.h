#pragma once
#include <allegro5\allegro.h>

//class enemy declarations
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
	void CreateEnemies(Enemy [], int , int );
	void SetEnemies(Enemy [], int );
	void DrawEnemies(Enemy [], int , int );
	void StartEnemies(Enemy [], int );
	void Collision(Enemy [], int , int );
	void Dead(Enemy [], int );
	void Apocalypse(Enemy [], int );


};