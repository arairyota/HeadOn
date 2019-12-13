#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Collision.h"
#include "Bullet.h"

#define MAX_ENEMY		(3)			//弾の最大表示
#define ENEMY_UP_SPEED	(4)
#define BOSS_UP_SPEED	(5)
#define ENEMY_SPEED		(8)		//弾のスピード
#define BOSS_SPEED		(16)
#define ENEMY_RATE		(20)		//弾の発射速度
#define ENEMY_AGE		(30)
#define ENEMY_MAX_LIFE	(2)
#define BOSS_MAX_LIFE	(30)
#define ENEMY_ACT		(500)		//
#define ENEMY_EMERGENCE	(100)		//

//////////////////////////////////////////////////////////////////////////////
//構造体宣言
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float PosX;
	float PosY;
	float SpeedX;
	float SpeedY;
	float RandomSpeedX;
	int Life;
	bool is_Enable;
	int FireFrame;
	CIRCLE Collision;
	BULLET Bullet;
} ENEMY;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void EnemyInit(void);
void EnemyCreate(void);
void EnemyUpdate(void);
void EnemyDraw(void);
void EnemyIs_Destroy(int cnt);
void BossIs_Destroy(void);
bool EnemyIs_Enable(int cnt);
bool BossIs_Enable(void);
void EnemyIs_Exp(int cnt);

const CIRCLE* Enemy_GetCircleCollsion(int cnt);
const CIRCLE* Boss_GetCircleCollsion(void);

#endif _ENEMY_H_
