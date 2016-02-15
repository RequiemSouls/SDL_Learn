cc = clang

SDL_LIB = -L/usr/lib/i386-linux-gnu -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/include/SDL2
EXE = SDL_Learn

all : $(EXE)

$(EXE) : main.o
	$(cc) $< $(SDL_LIB) -o $@

main.o : main.c
	$(cc) -c $(SDL_INCLUDE) $< -o $@

clean :
	rm *.o && rm $(EXE)