#include "common.h"
#include "Texture.h"
#include "sprite.h"
#include "Background.h"

BACKGROUND Background[LAYER][2];



void BackgroundInit(void)
{
	int cnt = 0;
	int cnt2 = 0;

	while (cnt < LAYER) {
		while (cnt2 < 2) {
			Background[cnt][cnt2].posX = cnt2 * SCREEN_WIDTH;
			Background[cnt][cnt2].posY = 0;
			cnt2++;
		}
		cnt2 = 0;
		cnt++;
	}

	/*for (int cnt = 0; cnt < LAYER; cnt++)
	{
		for (int cnt2 = 0; cnt2 < 1; cnt2++)
		{

			Background[cnt][cnt2].posX = cnt2 * 1280;
			Background[cnt][cnt2].posY = 0;
		}
	}*/
}

void BackgroundUpdate(void)
{
	int cnt = 0;
	int cnt2 = 0;

	while (cnt < LAYER) {
		while (cnt2 < 2) {
			if (Background[cnt][cnt2].posX <= -SCREEN_WIDTH)
			{
				Background[cnt][cnt2].posX = SCREEN_WIDTH;
			}
			Background[cnt][cnt2].posX -= 2 + cnt * 2; //SCREEN_SPEED(2)
			cnt2++;
		}
		cnt2 = 0;
		cnt++;
	}
	/*
	for (int cnt = 0; cnt < LAYER; cnt++)
	{
		for (int cnt2 = 0; cnt2 < 1; cnt2++)
		{
			Background[cnt][cnt2].posX -= 5 + cnt * 2;
		}
	}*/
}

void BackgroundDraw(void)
{
	int cnt = 0;
	int cnt2 = 0;

	while (cnt < LAYER) {
		while (cnt2 < 2) {
			SpriteDrawEx(TEXTURE_INDEX_BACKGROUND + cnt + 1, Background[cnt][cnt2].posX, 0, 0, 0, 1280, 720);
			cnt2++;
		}
		cnt2 = 0;
		cnt++;
	}
	/*
	for (int cnt = 0; cnt < LAYER; cnt++)
	{
		for (int cnt2 = 0; cnt2 < 1; cnt2++)
		{
			SpriteDrawEx(TEXTURE_INDEX_BACKGROUND + cnt + 1, Background[cnt][cnt2].posX, 0, 0, 0, 1280, 720);
		}
	}
	*/
}
