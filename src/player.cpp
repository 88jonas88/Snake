#include "../include/snakeGame.h"
#include "../include/player.h"
#include "../include/level.h"



COORDENADAS PLAYER::closest(){

	int minDist = MAX_VALUE;
    COORDENADAS minIndex;
    minIndex.x =0;
    minIndex.y = 0;

    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
           if (visited[i][j] == false)
           {
                if (cost[i][j] <  minDist)
                {
                    minDist = cost[i][j];

                    minIndex.x = i;
                    minIndex.y = j;
                }
           }
        }
    }
 
    return minIndex;
}

bool PLAYER::is_border()
{
    return near.x <= 0 or near.y <= 0 or near.x >= lines-1 or near.y >= cols-1;  
}

bool PLAYER::is_obstacle(){
  return mazeAux[near.x][near.y] == 1 or mazeAux[near.x][near.y] == 2 or mazeAux[near.x][near.y] == BODY or mazeAux[near.x][near.y] == HEAD;  
}

bool PLAYER::vizinho_obstacle(int a, int b){
  return mazeAux[a][b] == 1 or mazeAux[a][b] == 2 or mazeAux[a][b] == BODY or mazeAux[a][b] == HEAD;  
}

COORDENADAS PLAYER::get_neighbors(int a, int b){
    COORDENADAS vizinho;

 
        vizinho.x = a;
        vizinho.y = b;
    return vizinho;
}

COORDENADAS PLAYER::get_route(int a, int b)
{
    route.push_back(auxRote);

    auxRote.x  = prev[a][b].x;
    auxRote.y = prev[a][b].y;

    if (auxRote.x == iniPosX and auxRote.y == iniPosY)
    {
        auxRote.x  = prev[a][b].x;
        auxRote.y = prev[a][b].y;
        route.push_back(auxRote);        
        return auxRote;
    }

    
    return get_route(auxRote.x, auxRote.y);
}

std::vector<COORDENADAS> PLAYER::find_solution(int currentLevel){

    // reseta a rota
	route.clear();
    // currentMaze recebe o atual level a ser processado
	auto currentMaze = get_levels(currentLevel); //get o level considerando a posicao da cobra e todas as informacoes

    // quantidade de linhas e colunas
	lines = currentMaze.height;
	cols = currentMaze.width;

    // quantidade de celulas no labirinho
    int qtCelulas = lines * cols;

    //posicoes iniciais da cobra
	iniPosX = currentMaze.startX; 
	iniPosY = currentMaze.startY;

    //labirinto auxiliar para realizar operacoes
    mazeAux = currentMaze.maze; 

    // variaveis auxiliares para "zerar" a matrix PREV e os vizinhos
	COORDENADAS ZERO;
	ZERO.x = 0;
	ZERO.y = 0;

    // seta as matrizes como default
	for (int i = 0; i < lines; ++i)
	{
		std::vector< int > cosAux;
		std::vector< bool > boolAux;
		std::vector< COORDENADAS > coordAux;

		for (int j = 0; j < cols; ++j)
		{
			cosAux.push_back(MAX_VALUE);
			boolAux.push_back(UNDEFINED);
			coordAux.push_back(ZERO);
		}

		cost.push_back(cosAux);
		visited.push_back(boolAux);	
		prev.push_back(coordAux);

		cosAux.clear();
		boolAux.clear();
		coordAux.clear();
	}


 
    // set a celula inicial como a de menor custo
	cost[iniPosX][iniPosY] = 0;

   

	while(qtCelulas+1 > 0){ 

        near = closest(); // recebe a celula com menor custo
        visited[near.x][near.y] = true; // aqui da falha de segmentacao
           
      
        for (int i = 0; i < 4; ++i)
        {
            neighbors[i] = ZERO; 
        }

        if ( !is_obstacle())
        {
            //get todos os vizinhos da atual celula sendo processada
            if ( !vizinho_obstacle(near.x-1,near.y) )
                neighbors[0] = get_neighbors(near.x-1, near.y); 
            
            if ( !vizinho_obstacle(near.x+1,near.y) )
                neighbors[1] = get_neighbors(near.x+1, near.y);
            
            if ( !vizinho_obstacle(near.x,near.y-1) )
                neighbors[2] = get_neighbors(near.x, near.y-1);
            
            if ( !vizinho_obstacle(near.x,near.y+1) )
                neighbors[3] = get_neighbors(near.x, near.y+1);

        }

        // verifica se todos os vizinhos ao redor sao obstaculos
        if (     neighbors[0].x == 0  and neighbors[0].y == 0 
             and neighbors[1].x == 0  and neighbors[1].y == 0 
             and neighbors[2].x == 0  and neighbors[2].y == 0 
             and neighbors[3].x == 0  and neighbors[3].y == 0  )
        {
        
            endX = 0;
            endY = 0;
            break;
        }
        

        // custo total das celulas vizinhas ateh ao ponto original
        int totalCost = cost[near.x][near.y] + 1;

        for (int i = 0; i < 4; ++i)
        {
            if (neighbors[i].x != 0 and neighbors[i].y != 0 and totalCost < cost[neighbors[i].x][neighbors[i].y]) 
            {
                // adiciona o custo total em cada celula vizinha
                cost[neighbors[i].x][neighbors[i].y] = totalCost; 
                // armazena na celula vizinha qual foi a celula de quem ela veio, no caso eh a celula atual sendo processada
                prev[neighbors[i].x][neighbors[i].y].x = near.x; 
                prev[neighbors[i].x][neighbors[i].y].y = near.y;
            }
        }   
      

       //  printBackTracking();

        //verifica se a celula sendo processada eh a maca
        if (mazeAux[near.x][near.y] == FOOD)
        {
            endX = near.x;
            endY = near.y;
            break;
        }else{
            endX = 0;
            endY = 0;
        }

     
   

        qtCelulas--;

	}	

    //reseta todas as matrizes    
    prev.clear();
    cost.clear();
    visited.clear();
    mazeAux.clear();

    reset_apple(endX, endY, currentLevel);

    if (endX == 0  and endY == 0 ){
        route.clear();
        set_status(true);
    }
    else{
        auxRote.x = near.x;
        auxRote.y = near.y;
        set_status(false);
        get_route(endX, endY);
    }
    return route;
}



void PLAYER::printBackTracking(){


    std::system("clear");
    
    for (int i = 0; i < lines ; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << visited[i][j];
        }
        std::cout << std::endl;
    }
 
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}


