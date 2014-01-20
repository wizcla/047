#include "XInputEx.h"

/**
 * @brief		XInputGetStateEx�֐�
 * @author		Hiroki Tamura
 * @date		2013/06/11
 *
 * @param[in]	i_uiGamepadNumber	�Q�[���p�b�h�̔ԍ��i�O�`�R�j
 * @param[out]	o_pGamepad			�ΏۃQ�[���p�b�h�̓��͏��
 *
 * @return		�Ȃ� (none)
 */
void	XInputGetStateEx( UINT i_uiGamepadNumber, XINPUT_GAMEPAD_EX* o_pGamepad )
{
	XINPUT_STATE	padState ;
	::ZeroMemory( &padState, sizeof( XINPUT_STATE ) );

	//	: �p�b�h�̏�Ԃ��󂯎��i��P�����̓p�b�h�̔ԍ��łO����R�܂ł̒l�j
	o_pGamepad->bConnected	= XInputGetState( i_uiGamepadNumber, &padState ) == ERROR_SUCCESS ;
	if( !o_pGamepad->bConnected ) {
		return ;
	}
	
	//	: �����ꂽ�u�ԃt���O���Z�o
	o_pGamepad->wPressedButtons	= padState.Gamepad.wButtons & ~o_pGamepad->wButtons ;
	
	//	: XINPUT_GAMEPAD ���̃f�[�^���R�s�[
	::CopyMemory( o_pGamepad, &padState.Gamepad, sizeof(XINPUT_GAMEPAD) );
	
	//	: �X�e�B�b�N�̃f�[�^�����p�I�Ȓl�ɕϊ�����
	float	fLStickX	= float( padState.Gamepad.sThumbLX ) / 32768.0f ;	// -1.0f ���� +1.0f �͈̔͂ɂ���i���m�ɂ�+1.0f�ɂ͂Ȃ�Ȃ��B��� +0.999969f�j
	float	fLStickY	= float( padState.Gamepad.sThumbLY ) / 32768.0f ;	// -1.0f ���� +1.0f �͈̔͂ɂ���i���m�ɂ�+1.0f�ɂ͂Ȃ�Ȃ��B��� +0.999969f�j
	if( fLStickX > -0.25f && fLStickX < +0.25f &&
		fLStickY > -0.25f && fLStickY < +0.25f ) {	//	���S�̌덷�𖳎�����
		fLStickX	= 0.0f ;
		fLStickY	= 0.0f ;
	}
	o_pGamepad->fThumbLX	= fLStickX ;
	o_pGamepad->fThumbLY	= fLStickY ;

	float	fRStickX	= float( padState.Gamepad.sThumbRX ) / 32768.0f ;	// -1.0f ���� +1.0f �͈̔͂ɂ���i���m�ɂ�+1.0f�ɂ͂Ȃ�Ȃ��B��� +0.999969f�j
	float	fRStickY	= float( padState.Gamepad.sThumbRY ) / 32768.0f ;	// -1.0f ���� +1.0f �͈̔͂ɂ���i���m�ɂ�+1.0f�ɂ͂Ȃ�Ȃ��B��� +0.999969f�j
	if( fRStickX > -0.25f && fRStickX < +0.25f &&
		fRStickY > -0.25f && fRStickY < +0.25f ) {	//	���S�̌덷�𖳎�����
		fRStickX	= 0.0f ;
		fRStickY	= 0.0f ;
	}
	o_pGamepad->fThumbRX	= fRStickX ;
	o_pGamepad->fThumbRY	= fRStickY ;
}