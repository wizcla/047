#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"

GameScene::GameScene()
{
}

void	GameScene::Start()
{
	m_vecGameObjects.push_back( new Player );
	for( int i = 0 ; i < 20 ; i++ ) {
		m_vecGameObjects.push_back( new Enemy );
	}
}