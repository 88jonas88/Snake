#include "../include/level.h"
#include "../include/snakeGame.h"

int main(int argc, char const *argv[]) 
{
	SNAKEGAME game;

	game.initialize_game(argv[1] ); 
	
	while(game.over() == false) 
	{
		game.process_events();
		if (game.over() == false)
		{
			game.render();
		}
	}
	
	game.print_result();

	return 0;
}