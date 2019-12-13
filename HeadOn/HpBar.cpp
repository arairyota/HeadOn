#include "HpBar.h"
#include "Texture.h"
#include "sprite.h"
#include "Player.h"

static int cnt = 0;
static int RedBar = 0;
static int GreenBar = 0;
static int BlackBar = 0;

void HpBarInit(void){
	GreenBar = 300;
	RedBar = 300;
	BlackBar = 300;
	cnt = 0;
}

void HpBarUpdate(void) {
	//HP�����炷����
	if (cnt > 0)
	{
		RedBar -= 1;
		cnt--;
	}
}

void HpBarDraw(void) {
	SpriteDrawHp(TEXTURE_INDEX_BLACK, 300, 20, BlackBar, 20);
	SpriteDrawHp(TEXTURE_INDEX_REDBAR, 300, 20, RedBar, 20);		//�Ԃ̃o�[
	SpriteDrawHp(TEXTURE_INDEX_GREENBAR, 300, 20, GreenBar, 20);	//�΂̃o�[
	
}

void HpBarDamage(void) {
	GreenBar -= PLAYER_MAX_HP / PLAYER_MAX_LIFE;
	cnt += PLAYER_MAX_HP / PLAYER_MAX_LIFE;
}