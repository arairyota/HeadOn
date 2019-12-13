#ifndef _COLLSION_H_
#define _COLLSION_H_

typedef struct
{
	float cx, cy;		//中心座標
	float radius;		//半径
}CIRCLE;

							//アドレス先を書き換えない
bool Collision_is_HitCIRCLE(const CIRCLE* pCircleA, const CIRCLE* pCircleB);

#endif //_COLLSION_H_