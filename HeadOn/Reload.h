#ifndef RELOAD_H_
#define RELOAD_H_

#define MAX_CAPACITY	(120)		//�}�K�W�����e��
#define WAIT_TIME		(180)		//�����[�h����(1�b = 60)

typedef struct
{
	int Aeg = 0;
	int CerateFrame = 0;
	int capa = 0;

	bool is_Enable = false;
}RELOAD_DATA;

void Reload(void);

#endif // !RELOAD_H_
