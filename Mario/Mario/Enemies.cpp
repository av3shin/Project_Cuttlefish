#include "Enemies.h"

void Enemy::CreateEnemies(Enemy guys[], int size, int counter)
{
	int level = 0;
	int res_y = 0;

	if (level == 1)
	{

		for (int i = 0; i < size; i++) {
			guys[i].x = -10000;						//clears stage
			guys[i].y = -1000;
		}


		guys[0].x = 660; guys[0].y = 550;

		guys[1].x = 1410;
		guys[2].x = 1510;
		guys[21].x = 2490;
		guys[3].x = 2220;          //3050
		guys[4].x = 3370;
		guys[5].x = 4570;         //5150
		guys[6].x = 4470;
		guys[7].x = 4970;
		guys[8].x = 5880;
		guys[9].x = 6180;
		guys[10].x = 7250;
		guys[11].x = 7580;
		guys[12].x = 9020;
		guys[13].x = 9930;
		guys[14].x = 10130;
		guys[15].x = 11130;
		guys[16].x = 12035;
		guys[17].x = 12985;
		guys[18].x = 13685;
		guys[19].x = 14585;
		//guys[20].x = guys[19].x + 200;


		for (int i = 1; i < size; i++)
		{
			guys[i].y = res_y - 115;
		}

		guys[1].y = 450;
		//guys[2].y = 350;
		guys[3].y = 400;
		guys[6].y = 380;
		guys[12].y = 280;
		guys[9].y = 280;
		guys[8].y = 500;

	}//END OF STAGE 

}

void Enemy::SetEnemies(Enemy guys[], int size)
{

}

void Enemy::DrawEnemies(Enemy guys[], int size, int counter)
{

}

void Enemy::StartEnemies(Enemy guys[], int size)
{

}

void Enemy::Collision(Enemy guys[], int size, int counter)
{

}

void Enemy::Dead(Enemy guys[], int size)
{

}

void Enemy::Apocalypse(Enemy guys[], int size)
{

}