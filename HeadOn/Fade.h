#ifndef FADE_H_
#define FADE_H_
#include <d3dx9.h>

void FadeInit(void);
void FadeUpdate(void);
void FadeDraw(void);

void FadeStart(bool bOut, int frame, D3DCOLOR color);		//(trueでフェードアウト, 実行するタイミング, 使う色)

bool FadeIsFade(void);

#endif // !FADE_H_

