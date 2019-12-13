#ifndef _EXPLOSION_H_

#define _EXPLOSION_H_

#define MAX_EXPLOSION		(10)
#define MAX_PATTERN			(36)
#define PATTERN_WIDTH_MAX	(6)
#define PATTERN_HEIGHT_MAX	(6)
#define EXPLOSION_SCALE		(128)
#define EXPLOSION_WAIT_CNT	(5)

#include<d3dx9.h>

//////////////////////////////////////////////////////////////////////////////
//\‘¢‘ÌéŒ¾
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	float PositionX;
	float PositionY;

	int CerateFrame;
	int PatternCnt;
	int Aeg;

	bool is_Enable;
}EXPLOSION;

//#define EXPLOSION

void ExplosionInit(void);
void ExplosionCreate(float x, float y);
void ExplosionUpdate(void);
void ExplosionDraw(void);


//¶‚Ü‚ê‚½‚ÌƒtƒŒ[ƒ€”‚ğ•Û‘¶‚·‚é

#endif