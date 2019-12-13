//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "Score.h"
#include "common.h"

unsigned int Score = 0;

void ScoreInit(void)
{
	Score = 0;
}

void ScoreDraw(float x, float y, int score, int keta)
{
	//�J���X�g���l�����߂�
	int CountStopValue = 1;

	for (int i = 0; i < keta; i++)
	{
		CountStopValue *= 10;
	}

	//�J���X�g���Ă邩�ǂ���
	if (score >= CountStopValue)
	{
		score = CountStopValue - 1;
	}

	for (int i = keta - 1; i >= 0; i--)
	{
		//int n = score % 10;
		//float dx = (keta - 1) * NEMBER_WIDTH;
		NemberDraw(x + i * NEMBER_WIDTH, y, score % 10);
		score /= 10;
	}
}

void ScoreUpdate(void)
{
	Score += 100;
}

int GetScore(void)
{
	return Score;
}