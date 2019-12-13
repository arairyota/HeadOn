#ifndef TIMER_H_
#define TIMER_H_

//////////////////////////////////////////////////////////////////////////////
//É}ÉNÉçíËã`
//////////////////////////////////////////////////////////////////////////////
#define TIME_LIMIT (60)

void TimerInit(void);
void TimerUpdate(void);
void TimerUninit(void);
unsigned int TimerCnt(void); 
unsigned int TimerLimit(void);
void TimerDraw(float x, float y, int capacity, int keta);

#endif //TIME_H_