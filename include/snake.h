#ifndef _SANKE_
#define _SANKE_ value
	
#include "snakeGame.h"
#include "player.h"
#include "level.h"

class SNAKE : public LEVEL
{
	public:
		
		int size = 1;

		std::vector<COORDENADAS> routeSnake;
		void add_size();
		int get_size();
		void reset_size();
		
};	 

#endif