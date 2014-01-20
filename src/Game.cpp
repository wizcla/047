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

		//	: �Q�[���S�̂̍X�V���s��
		Scene*	pNextScene	= m_pScene->Update( *this );
		if( pNextScene != NULL ) {		// pNextScene��NULL�łȂ������ꍇ
			delete m_pScene ;			// ���݂̃V�[����j������
			m_pScene	= pNextScene ;	// �V�����󂯎�����V�[���ŏ㏑������
			m_pScene->Start();
		}

		begin();
		//	: �Q�[���S�̂̕`����s��
		m_pScene->Draw();

		end();
	}

	return 0 ;
}