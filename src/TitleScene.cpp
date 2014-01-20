#include "TitleScene.h"
#include "Enemy.h"

TitleScene::TitleScene()
{
};

void	TitleScene::Start()
{
	m_vecGameObjects.push_back( new Enemy );
}