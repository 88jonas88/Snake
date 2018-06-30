#include "../include/snakeGame.h"
#include "../include/snake.h"

LEVEL levelAux; 
PLAYER playAux;
SNAKE snakeAux;
void SNAKEGAME::initialize_game(const char * entrada)
{
	levelAux.read_levels(entrada); //faz a leiutura de todos os levels
}

void SNAKEGAME::process_events()
{		

	if (snakeAux.size == 1) // se o tamanho da cobra for 1, entao eh necessario setar uma pousicao antes
	{
		set_apple();
		
	}

	correctRoute = playAux.find_solution(currentLevel);	

}

void SNAKEGAME::render()
{	
	// numero de linhas e colunas do level atual
	int l = levelAux.levels[currentLevel].height;
	int c = levelAux.levels[currentLevel].width;

	std::reverse(correctRoute.begin(),correctRoute.end()); 
	
	// tamanho da snake e da rota a cada busca
	int tamanhoCobra = snakeAux.size;
	int tamanhoRota = (int)correctRoute.size();

	// set posicao inicial da cobra
	if (tamanhoCobra == 1)
		snakePosition.push_front( correctRoute[0] );
	else{
		
		snakePosition.push_front( correctRoute[1] );

	}

	int m = 1;

	while( m < tamanhoRota ){

		positionAux = snakePosition;

		// seta cabeca no labirinto

		auto top = positionAux.front();
		levelApple.maze[top.x][top.y] = HEAD;
		set_head(top.x, top.y, currentLevel);
		
		positionAux.pop_front();

		//seta a corpo no labirinto

		while( !positionAux.empty() )
		{
			top = positionAux.front();
			levelApple.maze[top.x][top.y] = BODY;
			set_body(top.x, top.y, currentLevel);
			positionAux.pop_front();
		}

		if (tamanhoCobra > 1)
		{
			top = snakePosition.front();
			levelApple.maze[top.x][top.y] = HEAD;
			set_head(top.x, top.y, currentLevel);
		}


		snakePosition.push_front( correctRoute[m] );


		// retira do deque a calda
		auto back = snakePosition.back();
		reset_body(back.x, back.y, currentLevel);
		snakePosition.pop_back();

		//Exibe no terminal a atual situal do tabuleiro
		show_status(l,c,levelApple);
		
		levelApple.maze[back.x][back.y] = PATH;

		m++;
	}
	// diminui a quantidade de comidas restantes
	levelAux.food--;
	snakeAux.add_size();

	correctRoute.clear();
	// seta a nova posicao inicial da cobra
	set_start_point(endX, endY, currentLevel);
	// seta a nova posicao da maca
	set_apple();

	// passa para o proximo nivel
	if (tamanhoCobra >= 5)
	{
		snakePosition.clear();
		snakeAux.reset_size();
		currentLevel++;
		levelAux.food = 5;
	}

	if (currentLevel == qtLevels and food == 0)
	{
		set_status(true);
	}


}


void SNAKEGAME::show_status(int l, int c, STRUCTLEVEL levelApple ){


	std::system("clear");

	std::cout << "Lives: ";
	for(int f = 0; f < levelAux.lives; f++){
		std::cout << "\u2764 ";
	}
	std::cout << "     ";
	/// Displays the food.
	std::cout << "Food: ";
	for(int f = 0; f < levelAux.food; f++){
		std::cout << "\u2605 ";
	}
	std::cout << std::endl;

	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			switch(levelApple.maze[i][j])
			{
				case PATH: std::cout << " ";
					break;
				case WALL: std::cout << "\u16E5";
					break;
				case BODY: std::cout << "o";
					break;
				case FOOD: std::cout << "\u2605";
						   endX = i;
						   endY = j;
					break;
				case INVISIBLEWALL: std::cout << " ";
					break;
				case STARTPOINT: std::cout << " ";
					break;
				case HEAD: std::cout << "@";
					break;
			}
		}
		std::cout << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


void SNAKEGAME::set_apple(){

	levelApple = get_levels(currentLevel);
	
	int a; //posicao x da apple
	int b; //posicao y da apple
	
	std::random_device rd;
	std::uniform_int_distribution<int> rand_r(1, levelApple.height-1);
	std::uniform_int_distribution<int> rand_c(1, levelApple.width-1);

	bool blocked(true);					

	while(blocked){
		/// Random position.
		auto rows = rand_r(rd);
		auto cols = rand_c(rd);

		if(levelApple.maze[rows][cols] == 0){			
			/// Determina a posicao da cobra
			a = rows;
			b = cols;
			blocked = false;
		}
	}
	// seta a nova posicao da maca
	set_apple_level(a, b, currentLevel);
	//atualiza o tabuleiro com a nova posicao da maca 
	levelApple = get_levels(currentLevel); 

}


bool SNAKEGAME::over(){
	auto aa = levelAux.get_status();
	result = aa;
	return aa;
}


void SNAKEGAME::print_result(){

	if (result == false)
	{
		std::cout << "VOCE VENCEU!!!" <<std::endl;
	}
	else{
		std::cout << "No solution for the next apple! YOU LOST!!!"<< std::endl;
	}

}
