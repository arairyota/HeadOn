#include "common.h"

RELOAD_DATA ReloadData;

unsigned int FrameCnt = 0;

//////////////////////////////////////////////////////////////////////////////
//関数名	: Reload
//戻り値	:
//説明		:
//引数		:
//////////////////////////////////////////////////////////////////////////////
void Reload(void)
{
	//リロードされてなかった場合
	if (!ReloadData.is_Enable && GetCapacity() < 120)
	{
		if (key.getTrigger(DIK_R))
		{
			GetBulletCapasity(0);
			ReloadData.CerateFrame = FrameCnt;
			ReloadData.is_Enable = true;
		}
	}

	//リロードされた場合
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