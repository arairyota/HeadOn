/*****************************************************************************
main.h
Aythor	: ���@��
Data	: 2017_04_19
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <d3dx9.h>
#include <windows.h>
#include <xaudio2.h>
#define	DisableLoad	(0x0800)

//���C�u���������N
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment (lib, "dinput8.lib")	//���͑��u���C�u����

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define PACKAGE_EDITOR
//#define MAP_EDITOR
//#define MOTION_EDITOR
//#define COLLISION_EDITOR
//#define GAME

#ifdef PACKAGE_EDITOR
#define CLASS_NAME	"PACKAGE_EDITOR"		//�E�B���h�E�̃N���X��
#endif // PACKAGE_EDITOR


#define WINDOW_NAME	"�E�B���h�E"	//�E�B���h�E�̖��O
#define SCREEN_WIDTH	(1280)		//�E�B���h�E�̍���
#define SCREEN_HEIGHT	(720)		//�E�B���h�E�̕�

#define TIMER_INTERVAL	(1000/60)	//�҂�����

#define NUM_VERTEX		(4)			//���_��
#define NUM_POLYGON		(2)			//�|���S����

#define PI				(3.141592f)	//�~����

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef D3DXCOLOR		Dcolor;
typedef D3DXMATRIX		Dmtx;
typedef D3DXQUATERNION	DQuate;
typedef D3DXMATRIX		DMtx;
typedef D3DXVECTOR3		Dvec3;
typedef D3DXVECTOR2		Dvec2;
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HWND getWnd(void);
int GetFPS(void);
POINT getClientSize();