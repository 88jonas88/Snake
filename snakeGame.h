#ifndef _SNAKEGAME_
#define _SNAKEGAME_ value

#include "level.h"
#include "player.h"

class SNAKEGAME : public LEVEL
{
public:
	// aqui vaificar as variaveis que monitoram o status do game,tipo vidas e macas
	LEVEL levelAux;
	std::vector<COORDENADAS> correctRoute;

	int endX;
	int endY;

	STRUCTLEVEL levelApple; // get o labirinto com  maca posicionada

	int currentLevel = 0;
	
	void initialize_game(const char *);
	void set_apple();

	void process_events();
	void render();
	
	COORDENADAS beginPoint;
	std::deque<COORDENADAS> snakePosition; 
	std::deque<COORDENADAS> positionAux;

	void show_status(int , int ,STRUCTLEVEL );

	bool over();

	bool result;
	void print_result();
};

#endif
