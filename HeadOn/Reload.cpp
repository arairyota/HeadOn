#include "common.h"

RELOAD_DATA ReloadData;

unsigned int FrameCnt = 0;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Reload
//�߂�l	:
//����		:
//����		:
//////////////////////////////////////////////////////////////////////////////
void Reload(void)
{
	//�����[�h����ĂȂ������ꍇ
	if (!ReloadData.is_Enable && GetCapacity() < 120)
	{
		if (key.getTrigger(DIK_R))
		{
			GetBulletCapasity(0);
			ReloadData.CerateFrame = FrameCnt;
			ReloadData.is_Enable = true;
		}
	}

	//�����[�h���ꂽ�ꍇ
	if(ReloadData.is_Enable)
	{
		ReloadData.Aeg = FrameCnt - ReloadData.CerateFrame;
		if (ReloadData.Aeg >= WAIT_TIME)
		{
			GetBulletCapasity(MAX_CAPACITY);
			ReloadData.is_Enable = false;
		}
		FrameCnt++;
	}
}