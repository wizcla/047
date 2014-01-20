#ifndef __Game_h__
#define	__Game_h__

#pragma	comment( lib, "d3dx9.lib" )

#include "WZGL\WZGL.h"
#include "xinputex\xinputex.h"
#include <vector>
class Scene ;

class Game
{
	Scene*	m_pScene ;	//	: �uGame�v�N���X�ɁuScene�v�N���X���W�񂳂�Ă���
	std::vector< XINPUT_GAMEPAD_EX > m_vecPads ;

public :
	Game();
	virtual ~Game();

	int	Run( void );

	//	�A�N�Z�b�T(�f�[�^�ɃA�N�Z�X���邽�߂̊֐�)
	//		�E�Z�b�^�[(set�`)	�E�Q�b�^�[(get�`)

	//	: �Q�b�^�[�̒�`
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
