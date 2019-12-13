#ifndef EFFECT_H_
#define EFFECT_H_
#include "common.h"

#define EFFECT_COUNT_MAX (2048)		//�G�t�F�N�g�̍ő吔


typedef struct
{
	float x, y;
	D3DCOLOR color;
	float alpha;
	float radius;
	int life;
	int birth;	//���܂ꂽ����
}EFFECT;

void EffectInit(void);
void EffectCreate(float x, float y, float radius, int life, D3DCOLOR color);
void EffectUpdate(void);
void EffectDraw(void);
void EffectUninit(void);

#endif // !EFFECT_H_

