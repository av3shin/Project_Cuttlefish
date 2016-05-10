#pragma once
//simple all encompassing, header file for all the entities within the game.
enum game { PLAYER, PROJECTILES, ENEMY };

class StillObstacles{
	public:
	int x;
	int y;
};

// Stationary Objects Section Start
class block: public StillObstacles
{
	/*int x;
	int y;*/
};

class Pipe : public StillObstacles
{
	/*int x;
	int y;*/
};

struct spike
{
	/*int x;
	int y;*/
	bool r = false;
	bool l = false;
	bool d = false;
};
// Stationary Objects Section End

// Moving Objects Section Start
class MovingObject{
public:
	int ID;
	bool alive;
	int boundx;
	int boundy;
};
struct enemies: public MovingObject
{
	/*int ID;
	int x;
	int y;
	bool alive;
	int boundx;
	int boundy;*/
};

struct Projectiles: public MovingObject
{
	/*int ID;
	int x;
	int y;
	bool live;
	int speed;*/
};
// Moving Objects Section End

void resize(int);
void jump(int);
