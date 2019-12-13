#include "common.h"
#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "EnemyBullet.h"


//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
static ENEMY Enemy[MAX_ENEMY];
static ENEMY Boss;
static int randomY;
static int randomY2;
static int randomY3;
static int DebugRandom;
static int SpeedRandom = 0;
static unsigned int Cnt;
bool g_bEnable = false;
static int DestroyCnt = 0;
//static CIRCLE g_EnemyCollision[MAX_ENEMY];
static int FrameCnt;

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	BulletInit
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void EnemyInit(void)
{
	FrameCnt = 0;

	DestroyCnt = 0;

	Cnt = 0;
	//�����𖈉�ς��鏈��
	srand((unsigned)time(NULL));

	for (int cnt = 0; cnt < MAX_ENEMY; cnt++)
	{
		Enemy[cnt].PosX = 0;
		Enemy[cnt].PosY = 0;
		Enemy[cnt].SpeedX = 0;
		Enemy[cnt].SpeedY = 0;
		Enemy[cnt].Life = ENEMY_MAX_LIFE;
		Enemy[cnt].is_Enable = false;
		//Enemy[cnt].FireFrame = cnt * BULLET_RATE;

		Enemy[cnt].Collision.cx = 0.0f;
		Enemy[cnt].Collision.cy = 0.0f;
		Enemy[cnt].Collision.radius = 50;	//�G�@�ɍ��킹��
		
	}

	Boss.PosX = 0;
	Boss.PosY = 0;
	Boss.SpeedX = 0;
	Boss.SpeedY = 0;
	Boss.Life = BOSS_MAX_LIFE;
	Boss.is_Enable = false;
	//Boss.FireFrame = cnt * BULLET_RATE;

	Boss.Collision.cx = 0.0f;
	Boss.Collision.cy = 0.0f;
	Boss.Collision.radius = 40;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	EnemyCreate
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void EnemyCreate(void) 
{
	randomY = (int)(rand() % (int)200);
	randomY2 = (int)(rand() % (int)200);

	randomY3 = randomY - randomY2;

	if (DestroyCnt < 30)
	{
		if (Cnt > ENEMY_RATE)
		{
			for (int cnt = 0; cnt < MAX_ENEMY; cnt++)
			{
				//�e�����݂��Ȃ�������
				if (!Enemy[cnt].is_Enable)
				{
					Enemy[cnt].PosX = SCREEN_WIDTH + 500;
					randomY = (int)(rand() % (int)200);
					randomY2 = (int)(rand() % (int)200);
					randomY3 = randomY - randomY2;
					DebugRandom = (int)(rand() % SCREEN_HEIGHT);
					Enemy[cnt].SpeedX = 0;
					
					Enemy[cnt].PosY = DebugRandom;
					Enemy[cnt].SpeedY = Enemy[cnt].PosY;
					Enemy[cnt].Life = ENEMY_MAX_LIFE;
					Enemy[cnt].is_Enable = true;
					cnt += MAX_ENEMY;
				}
			}
		}
		Cnt++;
	}

	if (DestroyCnt >= 30)
	{
		FrameCnt++;
		if (!Boss.is_Enable && FrameCnt > 300) {
			Boss.is_Enable = true;
			if (Cnt > ENEMY_RATE)
			{
				Boss.PosX = SCREEN_WIDTH + 500;
				randomY = (int)(rand() % (int)200);
				randomY2 = (int)(rand() % (int)200);
				randomY3 = randomY - randomY2;
				DebugRandom = (int)(rand() % SCREEN_HEIGHT);
				Boss.SpeedX = 0;

				Boss.PosY = DebugRandom;
				Boss.SpeedY = Boss.PosY;
				Boss.Life = BOSS_MAX_LIFE;
				Cnt = 0;
			}
			Cnt++;
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	EnemyUpdate
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void EnemyUpdate(void)
{
	for (int cnt = 0; cnt < MAX_ENEMY; cnt++)
	{
		//Enemy���L���ɂȂ�����
		if (Enemy[cnt].is_Enable)
		{
			Enemy[cnt].SpeedX -= ENEMY_SPEED;

			//�������
			if ((PlayerPositionX() + ENEMY_ACT) > Enemy[cnt].PosX)
			{
				if (Enemy[cnt].PosY < PlayerPositionY())
				{
					Enemy[cnt].SpeedY -= ENEMY_UP_SPEED;
				}

				else
				{
					Enemy[cnt].SpeedY += ENEMY_UP_SPEED;
				}
			}

			else
			{
				//�ǔ�����
				if (Enemy[cnt].PosY >= PlayerPositionY())
				{
					Enemy[cnt].SpeedY -= ENEMY_UP_SPEED;
				}

				if (Enemy[cnt].PosY <= PlayerPositionY())
				{
					Enemy[cnt].SpeedY += ENEMY_UP_SPEED;
				}
			}

			Enemy[cnt].PosX += (Enemy[cnt].SpeedX - Enemy[cnt].PosX) * 0.01f;
			Enemy[cnt].PosY += (Enemy[cnt].SpeedY - Enemy[cnt].PosY) * 0.05f;

			//���e������
			if (Enemy[cnt].PosX < -100)
			{
				//Enemy[cnt].is_Exp = true;
				Enemy[cnt].is_Enable = false;

			}

			//Enemy�̓����蔻��
			Enemy[cnt].Collision.cx = Enemy[cnt].PosX;
			Enemy[cnt].Collision.cy = Enemy[cnt].PosY;

			//Enemy�̒e�̏���
			EnemyBulletCreate(Enemy[cnt].PosX, Enemy[cnt].PosY, Enemy[cnt].is_Enable);
			
		}

		
	}

	

	if(Boss.is_Enable)
	{
		Boss.SpeedX -= BOSS_SPEED;
		//�ǔ�����
		if (Boss.PosY > PlayerPositionY())
		{
			Boss.SpeedY -= ENEMY_UP_SPEED * 3;
		}

		else
		{
			Boss.SpeedY += ENEMY_UP_SPEED * 3;
		}

		//�������
		if ((PlayerPositionX() + ENEMY_ACT) > Boss.PosX)
		{
			if (Boss.PosY < PlayerPositionY())
			{
				Boss.SpeedY -= ENEMY_UP_SPEED * 5;
			}

			else
			{
				Boss.SpeedY += ENEMY_UP_SPEED * 5;
			}
		}

		Boss.PosX += (Boss.SpeedX - Boss.PosX) * 0.01f;
		Boss.PosY += (Boss.SpeedY - Boss.PosY) * 0.1f;

		//���e������
		if (Boss.PosX <= -100)
		{
			//Enemy[cnt].is_Exp = true;
			//Boss.is_Enable = false;
   			Boss.PosX = SCREEN_WIDTH + 200;
			Boss.SpeedX = 0;
			Boss.PosY = DebugRandom;
			Boss.SpeedY = Boss.PosY;
		}

		Boss.Collision.cx = Boss.PosX;
		Boss.Collision.cy = Boss.PosY;

		//Enemy�̒e�̏���
		EnemyBulletCreate(Boss.PosX, Boss.PosY, Boss.is_Enable);
	}

	EnemyBulletUpdate();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	EnemytDraw
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void EnemyDraw(void)
{
	//SpriteDraw(TEXTURE_INDEX_BACKGROUND, 0, 0, 1280, 960);
	for (int cnt = 0; cnt < MAX_ENEMY; cnt++)
	{
		if (Enemy[cnt].is_Enable)
		{
			if (Enemy[cnt].is_Enable)
			{
				SpriteDrawEx(TEXTURE_INDEX_ENEMY, Enemy[cnt].PosX - 100, Enemy[cnt].PosY - 26, 0, 0, 200, 73);
				//Enemy[cnt].is_Exp = false;
				//Enemy[cnt].is_Enable = false;

			}
			EnemyBulletDraw(TEXTURE_INDEX_ENEMYBULLET, Enemy[cnt].PosX - 48, Enemy[cnt].PosY - 4, 97, 9, 0.5);
		}
	}

	if (Boss.is_Enable)
	{
		SpriteDrawEx(TEXTURE_INDEX_BOSS, Boss.PosX - 100, Boss.PosY - 26, 0, 0, 200, 73);
		//Enemy[cnt].is_Exp = false;
		//Enemy[cnt].is_Enable = false;
		EnemyBulletDraw(TEXTURE_INDEX_AKIYAMABULLET, Boss.PosX - 48, Boss.PosY - 26, 465, 324, 0.2);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: EnemyIs_Destroy
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void EnemyIs_Destroy(int cnt)
{
	Enemy[cnt].Life--; 
	if (Enemy[cnt].Life <= 0)
	{
  		Enemy[cnt].is_Enable = false;
		ExplosionCreate(Enemy[cnt].PosX - 128, Enemy[cnt].PosY - 128);
		DestroyCnt++;
		ScoreUpdate();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: BossIs_Destroy
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
void BossIs_Destroy(void)
{
	Boss.Life--;
	if (Boss.Life < 0)
	{
		Boss.is_Enable = false;
		ExplosionCreate(Boss.PosX - 128, Boss.PosY - 128);
		ScoreUpdate();
		SceneChange(SCENE_INDEX_RESULT);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: EnemyIs_Enable
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
bool EnemyIs_Enable(int cnt)
{
	return Enemy[cnt].is_Enable;
}

bool BossIs_Enable(void)
{
	return Boss.is_Enable;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Enemy_GetCircleCollsion
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
const CIRCLE* Enemy_GetCircleCollsion(int cnt)
{
	return &Enemy[cnt].Collision;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Boss_GetCircleCollsion
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
const CIRCLE* Boss_GetCircleCollsion(void)
{
	return &Boss.Collision;
}

