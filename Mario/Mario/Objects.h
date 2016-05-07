#pragma once
//simple all encompassing, header file for all the entities within the game.
enum game { PLAYER, PROJECTILES, ENEMY };

// Stationary Objects Section Start
struct block
{
	int x;
	int y;
};

struct Pipe
{
	int x;
	int y;
};

struct spike
{
	int x;
	int y;
	bool r = false;
	bool l = false;
	bool d = false;
};
// Stationary Objects Section End

// Moving Objects Section Start
struct enemies
{
	int ID;
	int x;
	int y;
	bool alive;
	int boundx;
	int boundy;
};

struct Projectiles
{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
};
// Moving Objects Section End

void resize(int);
void jump(int);
