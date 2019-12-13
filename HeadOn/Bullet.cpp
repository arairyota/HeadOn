//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "Bullet.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
static BULLET Bullet[MAX_BULLET];

static float g_BulletX = 0.0f;
static float g_BulletY = 0.0f;
static unsigned short int Capacity = MAX_CAPACITY;

//bool g_bBulletEnable = false;

//static int randomY;
static unsigned int Cnt;

//////////////////////////////////////////////////////////////////////////////
//関数名	:	BulletInit
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
void BulletInit(void)
{
	for (int cnt = 0; cnt < MAX_BULLET; cnt++)
	{
		Bullet[cnt].PosX = 0.0f;
		Bullet[cnt].PosY = 0.0f;
		Bullet[cnt].is_del = false;
		Bullet[cnt].is_Enable = false;
		Bullet[cnt].FireFrame = cnt * BULLET_RATE;
		Bullet[cnt].Collision.cx = 0.0f;
		Bullet[cnt].Collision.cy = 0.0f;
		Bullet[cnt].Collision.radius = 10;		//自弾に合わせて
	}

	Capacity = MAX_CAPACITY;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletCreate
//戻り値	:
//説明		:
//引数		: 弾の出現座標(X軸, Y軸)
//////////////////////////////////////////////////////////////////////////////
void BulletCreate(float px, float py)
{
	if (key.getPress(DIK_SPACE))
	{
		//もし弾がすでに有効だったら
		Cnt++;

		if (Cnt > BULLET_RATE)
		{
			for (int cnt = 0; cnt < MAX_BULLET; cnt++)
			{
				//弾が存在しなかったら
				if (!Bullet[cnt].is_Enable)
				{
					if (Capacity > 0)
					{
						Bullet[cnt].PosX = px;
						Bullet[cnt].PosY = py;

						Bullet[cnt].Collision.cx = px;
						Bullet[cnt].Collision.cy = py;

						Bullet[cnt].is_del = false;
						Bullet[cnt].is_Enable = true;
						cnt += MAX_BULLET;
						Capacity--;
						PlaySound(SOUND_LABEL_SE_SHOT);
					}
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
void BulletUpdate(void)
{
	for (int cnt = 0; cnt < MAX_BULLET; cnt++)
	{
		//弾が発射されたら
		if (Bullet[cnt].is_Enable)
		{
			//弾が着弾してなかったら
			if (!Bullet[cnt].is_del)
			{
				Bullet[cnt].PosX += BULLET_SPEED;
			}

			//着弾したら
			if (Bullet[cnt].PosX > SCREEN_WIDTH)
			{
				BulletDestroy(cnt);
				//Bullet[cnt].is_del = true;
				//Bullet[cnt].is_Enable = false;
			}

			Bullet[cnt].Collision.cx = Bullet[cnt].PosX;
			Bullet[cnt].Collision.cy = Bullet[cnt].PosY;
		}
	}
	Reload();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletDraw
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void BulletDraw(float px, float py)
{
	for (int cnt = 0; cnt < MAX_BULLET; cnt++)
	{
		if (Bullet[cnt].is_Enable)
		{
			SpriteDrawEx(TEXTURE_INDEX_PLAYERBULLET, Bullet[cnt].PosX, Bullet[cnt].PosY, 0, 0, 50, 9);
			Bullet[cnt].is_del = false;
			//Bullet[cnt].is_Enable = false;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletDestroy
//戻り値	:
//説明		: 
//////////////////////////////////////////////////////////////////////////////
void BulletDestroy(int cnt)
{
	Bullet[cnt].is_Enable = false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: BulletIs_Enable
//戻り値	:
//説明		: 
//////////////////////////////////////////////////////////////////////////////
bool BulletIs_Enable(int cnt)
{
	return Bullet[cnt].is_Enable;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Bullet_GetCircleCollision
//戻り値	:
//説明		:
//////////////////////////////////////////////////////////////////////////////
const CIRCLE* Bullet_GetCircleCollision(int cnt)
{
		return &Bullet[cnt].Collision;
}

void GetBulletCapasity(int Capa)
{
	Capacity = Capa;
}

int GetCapacity(void)
{
	return Capacity;
}