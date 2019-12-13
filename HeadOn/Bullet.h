#ifndef _BULLET_H_
#define _BULLET_H_

#include "Collision.h"

#define MAX_BULLET		(100)		//弾の最大表示
#define BULLET_SPEED	(50)		//弾のスピード
#define BULLET_RATE		(5)		//弾の発射速度

//////////////////////////////////////////////////////////////////////////////
//構造体宣言
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float PosX;
	float PosY;
	float Speed;
	bool is_del;
	bool is_Enable = {false};
	int FireFrame;
	CIRCLE Collision = {0};

} BULLET;


//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void BulletInit(void);
void BulletUpdate(void);
void BulletDraw(float px, float py);
void BulletCreate(float px, float py);
void BulletDestroy(int cnt);
bool BulletIs_Enable(int cnt);
void GetBulletCapasity(int Capa);
const CIRCLE* Bullet_GetCircleCollision(int num);
int GetCapacity(void);

#endif // !_BULLET_H_