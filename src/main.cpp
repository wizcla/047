#include "wzgl/wzgl.h"
#include "Game.h"
#include <time.h>

int	main()
{
	srand( (unsigned int)time( 0 ) );

	Game game ;
	return game.Run() ;
}