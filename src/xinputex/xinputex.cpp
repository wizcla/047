#include "XInputEx.h"

/**
 * @brief		XInputGetStateEx関数
 * @author		Hiroki Tamura
 * @date		2013/06/11
 *
 * @param[in]	i_uiGamepadNumber	ゲームパッドの番号（０～３）
 * @param[out]	o_pGamepad			対象ゲームパッドの入力状態
 *
 * @return		なし (none)
 */
void	XInputGetStateEx( UINT i_uiGamepadNumber, XINPUT_GAMEPAD_EX* o_pGamepad )
{
	XINPUT_STATE	padState ;
	::ZeroMemory( &padState, sizeof( XINPUT_STATE ) );

	//	: パッドの状態を受け取る（第１引数はパッドの番号で０から３までの値）
	o_pGamepad->bConnected	= XInputGetState( i_uiGamepadNumber, &padState ) == ERROR_SUCCESS ;
	if( !o_pGamepad->bConnected ) {
		return ;
	}
	
	//	: 押された瞬間フラグを算出
	o_pGamepad->wPressedButtons	= padState.Gamepad.wButtons & ~o_pGamepad->wButtons ;
	
	//	: XINPUT_GAMEPAD 分のデータをコピー
	::CopyMemory( o_pGamepad, &padState.Gamepad, sizeof(XINPUT_GAMEPAD) );
	
	//	: スティックのデータを実用的な値に変換する
	float	fLStickX	= float( padState.Gamepad.sThumbLX ) / 32768.0f ;	// -1.0f から +1.0f の範囲にする（正確には+1.0fにはならない。大体 +0.999969f）
	float	fLStickY	= float( padState.Gamepad.sThumbLY ) / 32768.0f ;	// -1.0f から +1.0f の範囲にする（正確には+1.0fにはならない。大体 +0.999969f）
	if( fLStickX > -0.25f && fLStickX < +0.25f &&
		fLStickY > -0.25f && fLStickY < +0.25f ) {	//	中心の誤差を無視する
		fLStickX	= 0.0f ;
		fLStickY	= 0.0f ;
	}
	o_pGamepad->fThumbLX	= fLStickX ;
	o_pGamepad->fThumbLY	= fLStickY ;

	float	fRStickX	= float( padState.Gamepad.sThumbRX ) / 32768.0f ;	// -1.0f から +1.0f の範囲にする（正確には+1.0fにはならない。大体 +0.999969f）
	float	fRStickY	= float( padState.Gamepad.sThumbRY ) / 32768.0f ;	// -1.0f から +1.0f の範囲にする（正確には+1.0fにはならない。大体 +0.999969f）
	if( fRStickX > -0.25f && fRStickX < +0.25f &&
		fRStickY > -0.25f && fRStickY < +0.25f ) {	//	中心の誤差を無視する
		fRStickX	= 0.0f ;
		fRStickY	= 0.0f ;
	}
	o_pGamepad->fThumbRX	= fRStickX ;
	o_pGamepad->fThumbRY	= fRStickY ;
}