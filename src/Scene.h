#ifndef __Scene_h__
#define __Scene_h__

#include <vector>
class Game ;
class GameObject ;

class Scene
{
protected :
	std::vector< GameObject* >	m_vecGameObjects ;

public :
	Scene();
	virtual ~Scene();
	
	virtual	void	Start( void )	= 0 ;
	Scene*	Update( const Game& i_Game );
	void	Draw();

	const std::vector< GameObject* >&	GetGameObjects( void )	const
	{
		return m_vecGameObjects ;
	}
};

#endif