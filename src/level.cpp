#include "../include/level.h"
#include "../include/snakeGame.h"

STRUCTLEVEL lv; //copia da struct
LEVEL levelClass;

LEVEL LEVEL::get_levels_class(){
	return levelClass;
}

STRUCTLEVEL LEVEL::get_levels(int currentlevel){
	return levelClass.levels[currentlevel];
}

void LEVEL::set_apple_level(int a, int b, int currentLevel){
	levelClass.levels[currentLevel].maze[a][b] = FOOD; // na classe level, na variavel levels[currentelevel] na posicao a,b do maze == food
}

void LEVEL::reset_apple(int a, int b, int currentLevel){
	levelClass.levels[currentLevel].maze[a][b] = PATH;
}
void LEVEL::set_start_point(int a, int b, int currentLevel){
	//reset ponto inicial
	int c = levelClass.levels[currentLevel].startX;
	int d = levelClass.levels[currentLevel].startY;
	
	levelClass.levels[currentLevel].maze[c][d] = PATH;

	levelClass.levels[currentLevel].startX = a;
	levelClass.levels[currentLevel].startY = b;
}

void LEVEL::set_body(int a, int b, int currentLevel){
    levelClass.levels[currentLevel].maze[a][b] = BODY;
}
void LEVEL::reset_body(int a, int b, int currentLevel){
    levelClass.levels[currentLevel].maze[a][b] = PATH;
}

void LEVEL::set_head(int a, int b, int currentLevel){
    levelClass.levels[currentLevel].maze[a][b] = HEAD;
}

void LEVEL::read_levels( std::string arqName ){

    std::ifstream arq(arqName); // abre o aquivo que contem os mapas de level
    std::string linhaBoard; // varivel para auxilar a leiura das linhas
    std::string tabuleiroAtual=""; // variavel que armazena tabuleiro por tabuleiro
    std::string skipLine; // variavel auxiliar

    if ( !arq.is_open() )
    {
       std::cout << "erro nao arquivo."<< std::endl;        
    }
    else
    {
        while(!arq.eof()){

            arq >> lv.height; // qt de linhas
            arq >> lv.width; // qt de colunas

            getline(arq, skipLine); //pula linha

            for( int i=0; i < lv.height; i++ ) // leitura do tabuleiro atual
            {
                getline( arq, linhaBoard );
                tabuleiroAtual += linhaBoard;
            }      

            setLevel(&lv, tabuleiroAtual); // seta tabuleiro na copia da classe

            getline(arq, skipLine); //pula linha
            tabuleiroAtual.clear();  //reseta string com o level
        }
    }
}

void LEVEL::setLevel(STRUCTLEVEL *lv, std::string levelAtual)
{
    int k = 0;

    for(int i = 0; i< lv->height; i++)
    {   
        std::vector<int> colsAux;
        for(int j = 0; j< lv->width; j++)
        {   
            switch( levelAtual[k] )
            {
                case ' ':   colsAux.push_back(PATH);
                    break;
                case '#':   colsAux.push_back(WALL);
                    break;
                case '.':   colsAux.push_back(INVISIBLEWALL);
                    break;
                case '*':   colsAux.push_back(STARTPOINT);
                            lv->startX = i;
                            lv->startY = j;
                    break;
                //default: // add funcao que para o programa por simbolo inesperado
            }
            k++;
        }
        lv->maze.push_back(colsAux);
        colsAux.clear();
    }

    levels.push_back(*lv); // seta a copia da classe no vetor que salva as copias
    levelClass.levels = levels;            
    lv->maze.clear(); // limpa copia do tabuleiro
    lv->width = 0;
    lv->height = 0;
    lv->startX = 0;
    lv->startY = 0;

    qtLevels++;
}   

void LEVEL::printAllMaze()
{   
    
    for(int m = 0; m < qtLevels; ++m)
    {
        std::cout << levels[m].height << "   " << levels[m].width << std::endl;
        std::cout << levels[m].startX << "   " << levels[m].startY << std::endl;

        for(int i = 0; i < levels[m].height; i++)
        {
            for(int j = 0; j< levels[m].width; j++)
            {
                std::cout << levels[m].maze[i][j];
            }
           std::cout << std::endl;
        }

        std::cout << std::endl;    
    }
    
}

void LEVEL::set_status(bool status){
    levelClass.over = status;
}

bool LEVEL::get_status()
{
    return levelClass.over;
}