#ifndef __XInputEx_h__
#define	__XInputEx_h__

#include <windows.h>
#include <xinput.h>
#pragma	comment( lib, "xinput.lib" )

//	: XINPUT_GAMEPAD �̊g���\����
struct XINPUT_GAMEPAD_EX	: public XINPUT_GAMEPAD
{
	//	�p�b�h���ڑ�����Ă����� true�A �ڑ�����Ă��Ȃ������� false
	bool	bConnected ;
	
	//	�A�i���O�X�e�B�b�N�̌X���� -1.0f �` +1.0f �̊Ԃɕϊ������f�[�^
	float	fThumbLX ;
	float	fThumbLY ;
	float	fThumbRX ;
	float	fThumbRY ;
	
	//	�e�{�^���ɑΉ������t���O�i�e�r�b�g�͉����ꂽ�u�Ԃ��� 1 �ɂȂ�j
	WORD	wPressedButtons ;

public :
	XINPUT_GAMEPAD_EX()
	{
		ZeroMemory( this, sizeof( XINPUT_GAMEPAD_EX ) );
	}
};

//	: �Q�[���p�b�h�̏�Ԃ��g���f�[�^���܂߂Ď擾����֐�
void	XInputGetStateEx( UINT i_uiGamepadNumber, XINPUT_GAMEPAD_EX* o_pGamepad );

#endif // !__XInputEx_h__