SDL_INC = $(shell pkg-config --cflags sdl2)
SDL_LINK = $(shell pkg-config --libs sdl2)

all:
	$(CXX) -o main $(SDL_INC) CApp.cpp $(SDL_LINK)
