#ifndef __Game_h__
#define	__Game_h__

#pragma	comment( lib, "d3dx9.lib" )

#include "WZGL\WZGL.h"
#include "xinputex\xinputex.h"
#include <vector>
class Scene ;

class Game
{
	Scene*	m_pScene ;	//	: 「Game」クラスに「Scene」クラスが集約されている
	std::vector< XINPUT_GAMEPAD_EX > m_vecPads ;

public :
	Game();
	virtual ~Game();

	int	Run( void );

	//	アクセッサ(データにアクセスするための関数)
	//		・セッター(set～)	・ゲッター(get～)

	//	: ゲッターの定義
	const std::vector< XINPUT_GAMEPAD_EX >&	GetPads( void )	const
	{
		return m_vecPads ;
	}

	const Scene&	GetScene( void )	const
	{
		return	*m_pScene ;
	}
};

#endif // !__Game_h__
