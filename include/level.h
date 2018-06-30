#ifndef _LEVEL_
#define _LEVEL_ value

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <random>
#include <chrono>
#include <thread>  

#include <algorithm>    // std::reverse
#include <deque>

enum typeCell
{
	PATH =0,
	WALL,
	INVISIBLEWALL,
	STARTPOINT,
	BODY,
	FOOD,
	HEAD
};
typedef struct
{
	int x;
	int y;
}COORDENADAS;

typedef struct
{
	int width; 
	int height;
	
	int startX;
	int startY;

	std::vector< std::vector< int > > maze;  // tabuleiro numerico
		
}STRUCTLEVEL;


class LEVEL 
{

	public:
		int lives = 5; 
		int food = 5;
		std::vector<STRUCTLEVEL> levels; // tabuleiros com todas as informacoes do level
		int qtLevels = 0;

		void read_levels( std::string );
		void setLevel(STRUCTLEVEL*, std::string);

		void printAllMaze();
		
		LEVEL get_levels_class();
		STRUCTLEVEL get_levels(int); // retorna apenas o strucnt que esta dentro da varivel level, para isso basta indicar qual o level
		void set_apple_level(int,int,int);
		void reset_apple(int,int,int);
		
		void set_start_point(int,int,int);

		void set_body(int, int ,int);
		void reset_body(int, int, int);

		void set_head(int, int ,int);
		
		void set_status(bool);
		bool get_status();
		bool over = false;


};

#endif