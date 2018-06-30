#ifndef _PLAYER_
#define _PLAYER_ value

#include "snakeGame.h"
#include "level.h"

#define MAX_VALUE 1000
#define UNDEFINED 0



class PLAYER : public LEVEL 
{
public:

	int endX;
	int endY;

	int iniPosX;
	int iniPosY;


	int lines;
	int cols;

	std::vector< std::vector<int> > mazeAux;
	
	std::vector<std::vector< COORDENADAS > > prev;
	std::vector<std::vector<int> > cost;
	std::vector< std::vector<bool> > visited;


	COORDENADAS near;

	std::vector<COORDENADAS> find_solution(int);

	COORDENADAS closest();

	COORDENADAS neighbors[4];


	bool is_border();
	bool is_obstacle();

	bool vizinho_obstacle(int , int);

	COORDENADAS get_neighbors(int,int);


	void printBackTracking();

	COORDENADAS get_route(int, int);

	std::vector<COORDENADAS> route;
	COORDENADAS auxRote;

	std::vector< std::vector< bool > > aaa;

};

#endif