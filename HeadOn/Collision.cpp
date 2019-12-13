#include "Collision.h"

//////////////////////////////////////////////////////////////////////////////
//ŠÖ”–¼	:	Collision_is_HitCIRCLE
//–ß‚è’l	:
//à–¾		:	“–‚½‚è”»’è(x“ñæ@+@y“ñæ = A‚ÆB‚Ì‹——£
//////////////////////////////////////////////////////////////////////////////

bool Collision_is_HitCIRCLE(const CIRCLE* pCircleA, const CIRCLE* pCircleB)
{
	float abr = pCircleA->radius + pCircleB->radius;

	float rr = (pCircleA->cx - pCircleB->cx) * (pCircleA->cx - pCircleB->cx) + (pCircleA->cy - pCircleB->cy) * (pCircleA->cy - pCircleB->cy); //r“ñæ = A“ñæ+B“ñæ

	return (abr * abr) > rr;
}