#ifndef _COLLSION_H_
#define _COLLSION_H_

typedef struct
{
	float cx, cy;		//���S���W
	float radius;		//���a
}CIRCLE;

							//�A�h���X������������Ȃ�
bool Collision_is_HitCIRCLE(const CIRCLE* pCircleA, const CIRCLE* pCircleB);

#endif //_COLLSION_H_