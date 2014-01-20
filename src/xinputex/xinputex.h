#ifndef __XInputEx_h__
#define	__XInputEx_h__

#include <windows.h>
#include <xinput.h>
#pragma	comment( lib, "xinput.lib" )

//	: XINPUT_GAMEPAD の拡張構造体
struct XINPUT_GAMEPAD_EX	: public XINPUT_GAMEPAD
{
	//	パッドが接続されていたら true、 接続されていなかったら false
	bool	bConnected ;
	
	//	アナログスティックの傾きを -1.0f ～ +1.0f の間に変換したデータ
	float	fThumbLX ;
	float	fThumbLY ;
	float	fThumbRX ;
	float	fThumbRY ;
	
	//	各ボタンに対応したフラグ（各ビットは押された瞬間だけ 1 になる）
	WORD	wPressedButtons ;

public :
	XINPUT_GAMEPAD_EX()
	{
		ZeroMemory( this, sizeof( XINPUT_GAMEPAD_EX ) );
	}
};

//	: ゲームパッドの状態を拡張データを含めて取得する関数
void	XInputGetStateEx( UINT i_uiGamepadNumber, XINPUT_GAMEPAD_EX* o_pGamepad );

#endif // !__XInputEx_h__