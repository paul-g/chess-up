SDL_INC = $(shell pkg-config --cflags sdl2)
SDL_LINK = $(shell pkg-config --libs sdl2)

%.o: %.cpp %.hpp
	$(CXX) -O3 -std=c++11 -c $(SDL_INC) $^

main: CApp.o Board.o Pawn.o
	$(CXX) -o main $(SDL_INC) $^ $(SDL_LINK)

clean:
	rm -f main *.o *.gch

run: main
	./main

.PHONY: run
