SDL_INC = $(shell pkg-config --cflags sdl2)
SDL_LINK = $(shell pkg-config --libs sdl2)


%.o: %.cpp %.hpp
	$(CXX) -O3 $(FLAGS) -std=c++11 -c $(SDL_INC) $^

main: CApp.o Board.o Pawn.o Piece.o Bishop.o Rook.o Queen.o Knight.o King.o
	$(CXX) -o main $(SDL_INC) $^ $(SDL_LINK) -lSDL2_ttf -lSDL2_image

clean:
	rm -f main *.o *.gch

debug:
	FLAGS="-O0 -g" make main


run: main
	./main

.PHONY: run
