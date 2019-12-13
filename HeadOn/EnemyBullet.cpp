//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "EnemyBullet.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
static BULLET EnemyBullet[ENEMY_MAX_BULLET];

static unsigned int Cnt;

//////////////////////////////////////////////////////////////////////////////
//関数名	:	BulletInit
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletInit(void)
{
	for (int cnt = 0; cnt < ENEMY_MAX_BULLET; cnt++)
	{
		EnemyBullet[cnt].PosX = 0.0f;
		EnemyBullet[cnt].PosY = 0.0f;
		EnemyBullet[cnt].is_del = false;
		EnemyBullet[cnt].is_Enable = false;
		EnemyBullet[cnt].FireFrame = cnt * ENEMY_BULLET_RATE;
		EnemyBullet[cnt].Collision.cx = 0.0f;
		EnemyBullet[cnt].Collision.cy = 0.0f;
		EnemyBullet[cnt].Collision.radius = 20;		//自弾に合わせて
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletCreate
//戻り値	:
//説明		:
//引数		: 弾の出現座標(X軸, Y軸)
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletCreate(float px, float py, bool is_Enable)
{
	if (is_Enable) {
		Cnt++;

		if (Cnt > ENEMY_BULLET_RATE)
		{
			for (int cnt = 0; cnt < ENEMY_MAX_BULLET; cnt++)
			{
				//弾が存在しなかったら
				if (!EnemyBullet[cnt].is_Enable)
				{
					EnemyBullet[cnt].PosX = px;
					EnemyBullet[cnt].PosY = py;

					EnemyBullet[cnt].Collision.cx = px;
					EnemyBullet[cnt].Collision.cy = py;

					EnemyBullet[cnt].is_del = false;
					EnemyBullet[cnt].is_Enable = true;
					cnt += MAX_BULLET;
				}
			}

			Cnt = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletUpdate
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletUpdate(void)
{
	for (int cnt = 0; cnt < ENEMY_MAX_BULLET; cnt++)
	{
		//弾が発射されたら
		if (EnemyBullet[cnt].is_Enable)
		{
			//弾が着弾してなかったら
			if (!EnemyBullet[cnt].is_del)
			{
				EnemyBullet[cnt].PosX -= (ENEMY_BULLET_SPEED + ENEMY_SPEED);
			}

			//着弾したら
			if (EnemyBullet[cnt].PosX < 0)
			{
				EnemyBullet[cnt].is_Enable = false;
				//Bullet[cnt].is_del = true;
				//Bullet[cnt].is_Enable = false;
			}

			EnemyBullet[cnt].Collision.cx = EnemyBullet[cnt].PosX;
			EnemyBullet[cnt].Collision.cy = EnemyBullet[cnt].PosY;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: EnemyBulletDraw
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletDraw(int texture, float px, float py, int tx, int ty, float size)
{
	for (int cnt = 0; cnt < ENEMY_MAX_BULLET; cnt++)
	{
		if (EnemyBullet[cnt].is_Enable)
		{
			SpriteDraw(texture, EnemyBullet[cnt].PosX, EnemyBullet[cnt].PosY, tx, ty, size);
			EnemyBullet[cnt].is_del = false;
			//Bullet[cnt].is_Enable = false;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletDestroy
//戻り値	:
//説明		: 
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletDestroy(int cnt)
{
	EnemyBullet[cnt].is_Enable = false;
	ExplosionCreate(EnemyBullet[cnt].PosX - 128, EnemyBullet[cnt].PosY - 128);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletIs_Enable
//戻り値	:
//説明		: 
//////////////////////////////////////////////////////////////////////////////
bool EnemyBulletIs_Enable(int cnt)
{
	return EnemyBullet[cnt].is_Enable;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Bullet_GetCircleCollision
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
const CIRCLE* EnemyBullet_GetCircleCollision(int cnt)
{
	return &EnemyBullet[cnt].Collision;
}