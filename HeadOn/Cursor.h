#ifndef CURSOR_H
#define CURSOR_H

typedef struct
{
	float posX;
	float posY;

	bool is_Right;
} CURSOR;

void CursorInit(void);
void CursorUpate(void);
void CursorDraw(int cursorNum);


#endif // !CURSOR_H
