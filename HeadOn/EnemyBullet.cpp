//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "EnemyBullet.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
static BULLET EnemyBullet[ENEMY_MAX_BULLET];

static unsigned int Cnt;

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	BulletInit
//�߂�l	:
//����		:
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
		EnemyBullet[cnt].Collision.radius = 20;		//���e�ɍ��킹��
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: BulletCreate
//�߂�l	:
//����		:
//����		: �e�̏o�����W(X��, Y��)
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletCreate(float px, float py, bool is_Enable)
{
	if (is_Enable) {
		Cnt++;

		if (Cnt > ENEMY_BULLET_RATE)
		{
			for (int cnt = 0; cnt < ENEMY_MAX_BULLET; cnt++)
			{
				//�e�����݂��Ȃ�������
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
//�֐���	: BulletUpdate
//�߂�l	:
//����		:
//����		:
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletUpdate(void)
{
	for (int cnt = 0; cnt < ENEMY_MAX_BULLET; cnt++)
	{
		//�e�����˂��ꂽ��
		if (EnemyBullet[cnt].is_Enable)
		{
			//�e�����e���ĂȂ�������
			if (!EnemyBullet[cnt].is_del)
			{
				EnemyBullet[cnt].PosX -= (ENEMY_BULLET_SPEED + ENEMY_SPEED);
			}

			//���e������
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
//�֐���	: EnemyBulletDraw
//�߂�l	:
//����		:
//����		:
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
//�֐���	: BulletDestroy
//�߂�l	:
//����		: 
//////////////////////////////////////////////////////////////////////////////
void EnemyBulletDestroy(int cnt)
{
	EnemyBullet[cnt].is_Enable = false;
	ExplosionCreate(EnemyBullet[cnt].PosX - 128, EnemyBullet[cnt].PosY - 128);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: BulletIs_Enable
//�߂�l	:
//����		: 
//////////////////////////////////////////////////////////////////////////////
bool EnemyBulletIs_Enable(int cnt)
{
	return EnemyBullet[cnt].is_Enable;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet_GetCircleCollision
//�߂�l	:
//����		:
//////////////////////////////////////////////////////////////////////////////
const CIRCLE* EnemyBullet_GetCircleCollision(int cnt)
{
	return &EnemyBullet[cnt].Collision;
}