#include "Game.h"
#include "Scene.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include <vector>

Enemy::Enemy()
	: GameObject( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), 30.0f, 0.0f, 0.0f )
{
	m_vPos.x	= float( rand() % 640 );
	m_vPos.y	= float( rand() % 480 );
}

Scene*	Enemy::Update( const Game& i_Game )
{
	//	: —á
	std::vector< GameObject* >	objs	= i_Game.GetScene().GetGameObjects();
	size_t	uiVecSize	= objs.size();
	for( size_t i = 0 ; i < uiVecSize ; i++ ) {
		if( objs[ i ]->IsHit( this ) ) {
			m_eState	= ObjectState::Dead ;
		}
	}

	const XINPUT_GAMEPAD_EX&	pad	= i_Game.GetPads()[ 0 ] ;
	if( pad.wPressedButtons & XINPUT_GAMEPAD_A ) {
		return new GameScene ;
	}

	return NULL ;
}

void	Enemy::Draw()
{
	fillStar( m_vPos.x, m_vPos.y, m_fHalf );
}