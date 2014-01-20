#ifndef __Player_h__
#define __Player_h__

#include "GameObject.h"
class Game ;

class Player : public GameObject
{
public :
	Player();

	Scene*	Update( const Game& i_Game );
	void	Draw();

	//	: ƒqƒbƒgŒn‚ÌŠÖ”
	bool	IsHit( Enemy* pEnemy );
};

#endif