#ifndef BACKGROUND_H
#define BACKGROUND_H

#define LAYER	(2)		//îwåiêîÅ[ÇP

typedef struct
{
	float posX;
	float posY;
}BACKGROUND;

void BackgroundInit(void);
void BackgroundUpdate(void);
void BackgroundDraw(void);

#endif // !BACKGROUND_H
