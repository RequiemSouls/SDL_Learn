cc = clang

SDL_LIB = -L/usr/lib/i386-linux-gnu -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/include/SDL2
EXE = SDL_Learn
OUT_DIR = ./bin

all : $(EXE)

$(EXE) : main.o
	$(cc) $< $(SDL_LIB) -o $(OUT_DIR)$@

main.o : main.c
	$(cc) -c -g $(SDL_INCLUDE) $< -o $(OUT_DIR)$@

clean :
	rm -rf $(OUT_DIR)
