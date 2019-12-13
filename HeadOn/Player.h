#ifndef PLAYER_H_
#define PLAYER_H_

#include "Collision.h"

//////////////////////////////////////////////////////////////////////////////
//íËêîíËã`
//////////////////////////////////////////////////////////////////////////////
#define PLAYERSPEED		(15)
#define PLAYER_MAX_LIFE	(5)
#define PLAYER_MAX_HP	(300)
typedef struct
{
	float posX;
	float posY;
	float SpeedX;
	float SpeedY;
	int Life;
	int Hp;
	int DamageCnt;
	CIRCLE Collision = { 0 };
}PLAYER;

void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);
const CIRCLE* Player_GetCircleCollision(void);
void PlayerDamage(void);
int PlayerLife(void);
float PlayerPositionY(void);
float PlayerPositionX(void);

#endif
