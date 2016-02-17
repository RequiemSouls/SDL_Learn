cc = clang

CFLAGS = -g -Wall -I/usr/include/SDL2
LDFLAGS = -L/usr/lib/i386-linux-gnu -lSDL2

SDL_Learn := main.c

all : $(SDL_Learn) sdlLearn

sdlLearn :
	$(cc) $(CFLAGS) -o $@ $(SDL_Learn) $(LDFLAGS)

clean :
	rm -f SDL_Learn
