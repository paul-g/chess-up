SDL_INC = $(shell pkg-config --cflags sdl2)
SDL_LINK = $(shell pkg-config --libs sdl2)

main:
	$(CXX) -o main $(SDL_INC) CApp.cpp $(SDL_LINK)

run: main
	./main

.PHONY: run
