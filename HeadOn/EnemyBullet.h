#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "Collision.h"

#define ENEMY_MAX_BULLET		(100)		//弾の最大表示
#define ENEMY_BULLET_SPEED		(10)		//弾のスピード
#define ENEMY_BULLET_RATE		(40)		//弾の発射速度

//////////////////////////////////////////////////////////////////////////////
//構造体宣言
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float PosX;
	float PosY;
	float Speed;
	bool is_del;
	bool is_Enable = { false };
	int FireFrame;
	CIRCLE Collision = { 0 };

} ENEMY_BULLET;


//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletInit(void);
void EnemyBulletUpdate(void);
void EnemyBulletDraw(int texture, float px, float py, int tx, int ty, float size);
void EnemyBulletCreate(float px, float py, bool is_Enable);
void EnemyBulletDestroy(int cnt);
bool EnemyBulletIs_Enable(int cnt);
void EnemyGetBulletCapasity(int Capa);
const CIRCLE* EnemyBullet_GetCircleCollision(int num);
//int GetCapacity(void);

#endif // !_ENEMYBULLET_H_