/*****************************************************************************
window�̕\��[main.cpp]
Aythor	:	�V��@�Ñ�
Data	:	2018/06/18
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
//#include "DebugPrintf.h"
#include <stdio.h>
#include "common.h"
#include "system_timer.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define CLASS_NAME		"�e�N�X�`��"
#define WINDOW_CAPTION	"�V���[�e�B���O�Q�[����b"	//���O�͂Ȃ�ł�����(�ۑ薼�Ƃ�)
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX))	//�X�^�C��

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
bool Init(HINSTANCE hInstance, HWND hWnd);
void Update(HWND hWnd);
void Draw(void);
void Uninit(void);

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
static unsigned short int TextureUV = 0;
static unsigned short int TextureUV_X = 0;
static unsigned short int TextureUV_Y = 0;
static unsigned int FrameCnt = 0;
static float g_rotation;


//FPS�J�E���^�[�p
static int g_FrameCounter = 0;
static int g_FPSBaseFrameCount = 0;
static double g_FPSBaseTime = 0.0;
//static double g_FPsBaseTime2 = 0.0;

//static float BulletSpeed = 0.0f;
//static float BulletPosX = 0.0f;


//////////////////////////////////////////////////////////////////////////////
//�֐���	:	APIENTRY WindMain
//�߂�l	:
//����		:	���C���֐�
//////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	//�ϐ��錾
	DWORD wind_style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);	//�X�^�C���ϐ��錾


	//�N���X�̓o�^
	WNDCLASS wc = {};									//�\���̂̏�������Y��Ȃ�, 0�ŏ������̏ȗ�
	wc.lpfnWndProc = WndProc;							//CALLBACK�֐��̓o�^
	wc.lpszClassName = CLASS_NAME;						//���O�͂Ȃ�ł�����
	wc.hInstance = hInstance;							//�C���X�^���X�n���h��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			//�}�E�X�J�[�\����ʏ��
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//�o�b�N�O���E���h�J���[(+1�͎d�l)


	RegisterClass(&wc);				//�V�X�e���ւ̓o�^

	 
	//��{��`���W
	RECT wind_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};		//RECT�\���̂ɕ��ƍ����������(��`)

	
	//�E�B���h�E�̗]���ȂƂ���𒲐�����
	AdjustWindowRect(
		&wind_rect,		//�擪�A�h���X
		WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),	//�E�B���h�X�^�C���t���O(�r�b�g)  ^ (�E�B���h�E�T�C�Y�����������ĕύX�ł��Ȃ����� | XOR���Z�q)
		FALSE			//�啶����BOOL
		);
		

	//�E�B���h�E�̃T�C�Y�m��
	unsigned short window_width = (unsigned short)(wind_rect.right - wind_rect.left);		//���v�Z
	unsigned short window_heigth = (unsigned short)(wind_rect.bottom - wind_rect.top);	//�����v�Z


	//�n�[�h�f�B�X�N���炢�낢��f�[�^������Ă�����
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);	//(�v���C�}�����j�^�[�̕�)
	int desktop_heigth = GetSystemMetrics(SM_CYSCREEN);	//(����)


	//��ʂ̒����ɕ\������ׂ̒l�����߂鏈��
	desktop_width = max((desktop_width - window_width) / 2, 0);
	desktop_heigth = max((desktop_heigth - window_heigth) / 2, 0);

	
	//�E�B���h�̐���			
	//�E�B���h��������ƃE�B���h�n���h�������炦��(�d�v)
	HWND hWnd = CreateWindow(
		CLASS_NAME,				//�N���X��(�֘A������������)
		WINDOW_CAPTION,			//�L���v�V����(�E�B���h�̃^�C�g��)
		wind_style,				//�E�B���h�X�^�C���t���O(�r�b�g)  ^ (�E�B���h�E�T�C�Y�����������ĕύX�ł��Ȃ����� | XOR���Z�q)
		desktop_width,			//X
		desktop_heigth,			//Y
		window_width,			//��
		window_heigth,			//����
		NULL,					//�e�̃E�B���h�E�n���h��(����͂Ȃ�����NULL)
		NULL,					//���j���[�n���h��(��ɓ�����)
		hInstance,				//�C���X�^���X�n���h��
		NULL					//���b�Z�[�W�ɑ���I���W�i���f�[�^�Ȃǂ̃|�C���^
		);


	//hWnd == NULL retrun 0 or -1�ŏ����悤�ɂ��� or ���b�Z�[�WBox�Ōx�����o��


	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);		//ShowWindow�Ō��� �Ƃ肠������nCmdShow


	//���b�Z�[�W���� or ���b�Z�[�W���[�v(���[�v���������ď���҂�)
	MSG msg = {};

	Init(hInstance, hWnd);

	//�S�̂̃��[�v
	do{ 
			//�������b�Z�[�W����������
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			//�Ȃ�������
			else
			{
				//�Q�[������
				Update(hWnd);
				Draw();
				SceneCheck();
				//g_FrameBaseTime = SystemTimer_GetTime();
			}

		} while (msg.message != WM_QUIT);


	return (int)msg.wParam;

}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)	//DispatchMessage�Ƃقړ���������
	{
	case WM_KEYDOWN:		//esckey�������ꂽ��
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if(MessageBox(hWnd,"�I�����܂���?", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);
		}

		return 0;	//���߂Ȃ�Ȃ��������Ƃɂ���

	case WM_DESTROY:		//�E�B���h�E�̔j�����b�Z�[�W
		PostQuitMessage(0);		
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//���ʂ̃��b�Z�[�W�������肷��(��点�����Ȃ����Ƃ������ɂ����)

}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	Init
//�߂�l	:
//����		:	������
//////////////////////////////////////////////////////////////////////////////
bool Init(HINSTANCE hInstance, HWND hWnd)
{
	key.init(hInstance, hWnd);
	mouse.init(hInstance, hWnd);

	InitSound(hWnd);

	Direct3D_Init(hWnd);

	SceneInit(SCENE_INDEX_TITTLE);

	FadeInit();			//�t�F�[�h������

	if (!Direct3D_Init(hWnd))
	{
		//messegebox�Ŏ��s��������
		MessageBox(hWnd, "�擾���s", "�G���[", MB_OK);
	}

	LPDIRECT3DDEVICE9 g_pD3DDev = Direct3D_GetDevice();
	
	g_pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);			//�e�N�X�`���T���v���[�ݒ� p228(0, �A�h���b�V���O���[�h�t�����ݒ� )�ޏ��ƍ��R��������ɏZ������

	g_pD3DDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	
	
	g_pD3DDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		//�e�N�X�`���t�B���^�����O p232 

	g_pD3DDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		//�|���S�����W��0.5�ɂ��炷�ƐF�������Ȃ�Ȃ�

	g_pD3DDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);		//�g��k���̑����Q�[���ɐݒ�

	g_pD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���u�����f�B���O��L��(�ޏ��̐��i�ݒ�,���܂�ς�������ƝX�˂�)
	g_pD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			//�`�挳�ݒ�
	g_pD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//�`���ݒ�

	//�������̌v�Z���𖳗����ς��� �ォ�� ����* �E��
	g_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		//(�e�N�X�`���X�e�[�W��, ���ӒlD3D)����Z
	g_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);		//(							�E�Ӓl)�|���S���J���[
	g_pD3DDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		//���f�����[�g�@���@*
	
	//�V�X�e���^�C�}�[������
	SystemTimer_Initialize();

	//�^�C�}�[�X�^�[�g
	SystemTimer_Start();

	g_FPSBaseFrameCount = 0;

	g_FPSBaseTime = SystemTimer_GetTime();

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	Update
//�߂�l	:
//����		:	�X�V
//////////////////////////////////////////////////////////////////////////////
void Update(HWND hWnd)
{
	key.update();
	mouse.update();

	FadeUpdate();

	SceneUpdate();

	FrameCnt++;

	//g_rotation += 0.01f;

	//rx = px * cos(rad) - py * sin(rad);
	//ry = px * sin(rad) + py * cos(rad);

	/*TextureUV = (FrameCnt / WAIT_FRAME) % 10;

	TextureUV_X = (700 / 5) * (TextureUV % 5);

	TextureUV_Y = (400 / 2) * (TextureUV / 5);
	*/

	
	g_FrameCounter++;

	double time = SystemTimer_GetTime();

	if (time - g_FPSBaseTime > 1.0f)
	{
		char buf[256];
		sprintf(buf, "%.2f fps", (g_FrameCounter - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));
		SetWindowText(hWnd, buf);

		g_FPSBaseTime = time;
		g_FPSBaseFrameCount = g_FrameCounter;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	Draw
//�߂�l	:
//����		:	�`��
//////////////////////////////////////////////////////////////////////////////
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 255, 255, 255), 1.0f, 0);	//��ʃN���A TARGET �F�N���A Z_BUFFER �[�� 0����Ԏ�O 1����Ԍ��
	pDevice->BeginScene();

	SceneDraw();

	FadeDraw();

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);	//�O��ʂ̌���ʂ�ς��鏈��
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	Uninit
//�߂�l	:
//����		:	�I��
//////////////////////////////////////////////////////////////////////////////
void Uninit(void)
{
	key.uninit();
	mouse.uninit();
	Texture_Release();
	Direct3D_Uninit();
	SceneUnInit();
	EffectUninit();
	UninitSound();
}