#ifndef __Enemy_h__
#define	__Enemy_h__

#include "GameObject.h"
class Game ;

class Enemy	: public GameObject
{
public :
	Enemy();

	Scene*	Update( const Game& i_Game );
	void	Draw();
};

#endif // !__Enemy_h__
