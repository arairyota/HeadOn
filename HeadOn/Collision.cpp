#include "Collision.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	Collision_is_HitCIRCLE
//�߂�l	:
//����		:	�����蔻��(x���@+�@y��� = A��B�̋���
//////////////////////////////////////////////////////////////////////////////

bool Collision_is_HitCIRCLE(const CIRCLE* pCircleA, const CIRCLE* pCircleB)
{
	float abr = pCircleA->radius + pCircleB->radius;

	float rr = (pCircleA->cx - pCircleB->cx) * (pCircleA->cx - pCircleB->cx) + (pCircleA->cy - pCircleB->cy) * (pCircleA->cy - pCircleB->cy); //r��� = A���+B���

	return (abr * abr) > rr;
}