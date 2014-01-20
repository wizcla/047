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

	//	: ゲームオブジェクトの更新処理
	for( size_t i = 0 ; i < uiVecSize ; i++ ) {
		Scene*	pNextScene	= m_vecGameObjects[ i ]->Update( i_Game );
		if( pNextScene != NULL ) {
			return pNextScene ;
		}
	}

	//	: 破棄が必要なゲームオブジェクトに対する処理
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