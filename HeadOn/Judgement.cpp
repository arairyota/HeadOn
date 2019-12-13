//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "Judgement.h"
#include"common.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Timer.h"
#include "EnemyBullet.h"
#include "GameOver.h"

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ��錾
//////////////////////////////////////////////////////////////////////////////
static int cnt = 0;
static int cnt2 = 0;
static int cnt3 = 0;

//////////////////////////////////////////////////////////////////////////////
//�֐���	:
//�߂�l	:
//����		:	�S�Ẵ��[���������ǂ�
//////////////////////////////////////////////////////////////////////////////
void JudgementUpdate(void)
{
	for (cnt2 = 0; cnt2 < MAX_ENEMY; cnt2++)
	{
		// Enemy���L�����H
		if (EnemyIs_Enable(cnt2))
		{
			//Player��Enemy�̓����蔻��
			if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), Enemy_GetCircleCollsion(cnt2)))
			{
				//�v���C���[�_���[�W����
				PlayerDamage();
				EnemyIs_Destroy(cnt2);

				
			}

			//�v���C���[�̒e�̕�������
			for (cnt = 0; cnt < MAX_BULLET; cnt++)
			{
				// �v���C���[�̒e�ƓG�Ƃ̓����蔻��
				// �v���C���[�̒e���L�����H
				if (BulletIs_Enable(cnt))
				{
					// �v���C���[�̒e�̃R���W�����ƓG�̃R���W�����Ƃ̓����蔻��
					if (Collision_is_HitCIRCLE(Bullet_GetCircleCollision(cnt), Enemy_GetCircleCollsion(cnt2)))
					{
						// �������Ă���v���C���[�̒e�ƓG������
						BulletDestroy(cnt);
						EnemyIs_Destroy(cnt2);
						//ScoreUpdate();
					}
				}
			}

			//�v���C���[�@�ƓG�̒e�̃R���W���������蔻��
			for (cnt3 = 0; cnt3 < ENEMY_MAX_BULLET; cnt3++)
			{
				if (EnemyBulletIs_Enable(cnt3))
				{
					if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), EnemyBullet_GetCircleCollision(cnt3)))
					{
 						EnemyBulletDestroy(cnt3);
						PlayerDamage();
					}
				}
			}
		}	
	}

	
	// �{�X���L�����H
	if (BossIs_Enable())
	{
		//Player��Boss�̓����蔻��
		if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), Boss_GetCircleCollsion()))
		{
			//�v���C���[�_���[�W����
			PlayerDamage();
			BossIs_Destroy();


			//��ʈړ��i�v���F�v���C���[���S�j
			if (PlayerLife() <= 0)
			{
				SceneChange(SCENE_INDEX_RESULT);
				FadeStart(true, 10, D3DCOLOR_RGBA(0, 0, 0, 255));
			}
		}

		//�e�̕�������
		for (cnt = 0; cnt < MAX_BULLET; cnt++)
		{
			// �v���C���[�̒e�ƓG�Ƃ̓����蔻��
			// �v���C���[�̒e���L�����H
			if (BulletIs_Enable(cnt))
			{
				// �v���C���[�̒e�̃R���W�����ƓG�̃R���W�����Ƃ̓����蔻��
				if (Collision_is_HitCIRCLE(Bullet_GetCircleCollision(cnt), Boss_GetCircleCollsion()))
				{
					// �������Ă���v���C���[�̒e�ƓG������
					BulletDestroy(cnt);
					BossIs_Destroy();
					//ScoreUpdate();
				}
			}
		}
		//�v���C���[�@�ƓG�̒e�̃R���W���������蔻��
		for (cnt3 = 0; cnt3 < ENEMY_MAX_BULLET; cnt3++)
		{
			if (EnemyBulletIs_Enable(cnt3))
			{
				if (Collision_is_HitCIRCLE(Player_GetCircleCollision(), EnemyBullet_GetCircleCollision(cnt3)))
				{
					EnemyBulletDestroy(cnt3);
					PlayerDamage();
				}
			}
		}

	}
	//��ʃ`�F���W�i�v��:�^�C���A�b�v�j
	if (TimerCnt()  /60 > TIME_LIMIT || PlayerLife() < 1)
	{
		SceneChange(SCENE_INDEX_GAMEOVER);
		FadeStart(true, 10, D3DCOLOR_RGBA(0, 0, 0, 255));
	}
}