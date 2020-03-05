all: mm

mm: main.o Player.o Map.o barrels.o Game.o Monkey.o button.o MainMenu.o
	g++ main.o Player.o button.o Monkey.o barrels.o Map.o MainMenu.o Game.o -o mm -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

MainMenu.o: MainMenu.cpp
	g++ -c MainMenu.cpp

button.o: button.cpp
	g++ -c button.cpp

Monkey.o: Monkey.cpp
	g++ -c Monkey.cpp

Game.o: Game.cpp
	g++ -c Game.cpp

barrels.o: barrels.cpp
	g++ -c barrels.cpp

main.o: main.cpp
	g++ -c main.cpp

Map.o: Map.cpp
	g++ -c Map.cpp

Player.o: Player.cpp
	g++ -c Player.cpp
clean: 
	rm -rf *o mm
