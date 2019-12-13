#ifndef DAMAGE_EFECT_H
#define DAMAGE_EFECT_H

#define SMOKE_RATE		(5)

typedef struct
{
	float PosX;
	float PosY;

	int Age;
	int Now;
	float SmokeSize;

	bool is_Enable;
}DAMAGEEFECT;

void DamageEfectInit(void);
void DamageEfectCreate(float px, float py);
void DamageEfectUpdate(void);
void DamageEfectDraw(int color);


#endif // !DAMAGE_EFECT_H
