all:	
	g++ -Wall -pedantic -ansi -std=c++11 -o snake -I include src/main.cpp src/level.cpp src/snakeGame.cpp src/player.cpp src/snake.cpp

clean:
	rm snake