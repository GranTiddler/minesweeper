
output: main.o button.o
	g++ main.o -o minesweep -lsfml-graphics -lsfml-window -lsfml-system button.o
	./minesweep


main.o: main.cpp
	g++ -c main.cpp

button.o: button.hpp button.cpp
	g++ -c button.cpp

clean:
	rm *.o


target: dependencies
	action