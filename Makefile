SDL_INC = $(shell pkg-config --cflags sdl2)
SDL_LINK = $(shell pkg-config --libs sdl2)

main: CApp.cpp CApp.hpp
	$(CXX) -std=c++11 -o main $(SDL_INC) CApp.cpp $(SDL_LINK)

clean:
	rm main

run: main
	./main

.PHONY: run
