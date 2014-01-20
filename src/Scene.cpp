#include "Game.h"
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	size_t	uiVecSize	= m_vecGameObjects.size();
	for( size_t i = 0 ; i < uiVecSize ; i++ ) {
		delete m_vecGameObjects[ i ] ;
	}
	m_vecGameObjects.clear();
}

Scene*	Scene::Update( const Game& i_Game )
{
	size_t uiVecSize	= m_vecGameObjects.size();

	//	: �Q�[���I�u�W�F�N�g�̍X�V����
	for( size_t i = 0 ; i < uiVecSize ; i++ ) {
		Scene*	pNextScene	= m_vecGameObjects[ i ]->Update( i_Game );
		if( pNextScene != NULL ) {
			return pNextScene ;
		}
	}

	//	: �j�����K�v�ȃQ�[���I�u�W�F�N�g�ɑ΂��鏈��
	std::vector< GameObject* >::iterator	it	= m_vecGameObjects.begin();
	while( it != m_vecGameObjects.end() ) {
		if( (*it)->GetState() == ObjectState::Dead ) {
			it	= m_vecGameObjects.erase( it );
		}
		else {
			it++ ;
		}
	}

	return NULL ;
}

void	Scene::Draw()
{
	size_t uiVecSize	= m_vecGameObjects.size();
	for( size_t i = 0 ; i < uiVecSize ; i++ ) {
		m_vecGameObjects[ i ]->Draw();
	}
}