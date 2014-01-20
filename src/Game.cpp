#include "Game.h"
#include "GameScene.h"
#include "TitleScene.h"

Game::Game()
	: m_pScene( new TitleScene )
{
	m_vecPads.push_back( XINPUT_GAMEPAD_EX() );
	m_vecPads.push_back( XINPUT_GAMEPAD_EX() );
	m_vecPads.push_back( XINPUT_GAMEPAD_EX() );
	m_vecPads.push_back( XINPUT_GAMEPAD_EX() );
}

Game::~Game()
{
	delete m_pScene ;
}

int	Game::Run( void )
{
	m_pScene->Start();

	while( true ) {
		size_t	uiVecSize	= m_vecPads.size();
		for( size_t i = 0 ; i < uiVecSize ; i++ ) {
			XInputGetStateEx( i, &m_vecPads[ i ] );
		}

		//	: ゲーム全体の更新を行う
		Scene*	pNextScene	= m_pScene->Update( *this );
		if( pNextScene != NULL ) {		// pNextSceneがNULLでなかった場合
			delete m_pScene ;			// 現在のシーンを破棄して
			m_pScene	= pNextScene ;	// 新しく受け取ったシーンで上書きする
			m_pScene->Start();
		}

		begin();
		//	: ゲーム全体の描画を行う
		m_pScene->Draw();

		end();
	}

	return 0 ;
}