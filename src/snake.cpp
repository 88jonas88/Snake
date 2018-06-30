#include "../include/snakeGame.h"
#include "../include/player.h"
#include "../include/level.h"
#include "../include/snake.h"

SNAKE snake;
//Soma o tamanho da cobra
void SNAKE::add_size(){
	size += 1;
}

int SNAKE::get_size(){
	return size;
}
// reseta o tamanho da cobra para o proximo level
void SNAKE::reset_size(){
	size = 1;
}