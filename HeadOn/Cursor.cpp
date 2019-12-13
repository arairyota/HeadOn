#include "common.h"
#include "Cursor.h"
#include "Texture.h"
#include "sprite.h"
#include "Timer.h"

CURSOR Cursor;

void CursorInit(void)
{
	Cursor.posX = 420;
	Cursor.posY = 430;

	Cursor.is_Right = false;
}

void CursorUpate(void)
{
	if (TimerCnt() / 60 % 2 == 1){
		if (Cursor.is_Right){
			Cursor.posX += 32;
			Cursor.is_Right = false;
		}
	}

	if (TimerCnt() / 60 % 2 == 0) {
		if (!Cursor.is_Right) {
			Cursor.posX -= 32;
			Cursor.is_Right = true;
		}
	}

}

void CursorDraw(int cursorNum)
{
	SpriteDraw(TEXTURE_INDEX_AKIYAMACURSOR, Cursor.posX, Cursor.posY + cursorNum * 100, 465, 323, 0.1);
}
