//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "Bullet.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
static BULLET Bullet[MAX_BULLET];

static float g_BulletX = 0.0f;
static float g_BulletY = 0.0f;
static unsigned short int Capacity = MAX_CAPACITY;

//bool g_bBulletEnable = false;

//static int randomY;
static unsigned int Cnt;

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	BulletInit
//�߂�l	:
//����		:
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
		Bullet[cnt].Collision.radius = 10;		//���e�ɍ��킹��
	}

	Capacity = MAX_CAPACITY;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: BulletCreate
//�߂�l	:
//����		:
//����		: �e�̏o�����W(X��, Y��)
//////////////////////////////////////////////////////////////////////////////
void BulletCreate(float px, float py)
{
	if (key.getPress(DIK_SPACE))
	{
		//�����e�����łɗL����������
		Cnt++;

		if (Cnt > BULLET_RATE)
		{
			for (int cnt = 0; cnt < MAX_BULLET; cnt++)
			{
				//�e�����݂��Ȃ�������
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
//�֐���	: BulletUpdate
//�߂�l	:
//����		:
//����		:
//////////////////////////////////////////////////////////////////////////////
void BulletUpdate(void)
{
	for (int cnt = 0; cnt < MAX_BULLET; cnt++)
	{
		//�e�����˂��ꂽ��
		if (Bullet[cnt].is_Enable)
		{
			//�e�����e���ĂȂ�������
			if (!Bullet[cnt].is_del)
			{
				Bullet[cnt].PosX += BULLET_SPEED;
			}

			//���e������
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
//�֐���	: BulletDraw
//�߂�l	:
//����		:
//����		:
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
//�֐���	: BulletDestroy
//�߂�l	:
//����		: 
//////////////////////////////////////////////////////////////////////////////
void BulletDestroy(int cnt)
{
	Bullet[cnt].is_Enable = false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: BulletIs_Enable
//�߂�l	:
//����		: 
//////////////////////////////////////////////////////////////////////////////
bool BulletIs_Enable(int cnt)
{
	return Bullet[cnt].is_Enable;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet_GetCircleCollision
//�߂�l	:
//����		:
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