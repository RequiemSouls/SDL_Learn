cc = clang

CFLAGS = -g -Wall
LDFLAGS =

UNAME = $(shell uname)
SYS = $(if $(filter Linux%,$(UNAME)),linux,\
		$(if $(filter MINGW%,$(UNAME)),mingw,\
		$(if $(filter Darwin%,$(UNAME)),macosx,\
			undefined\
)))

SDL_Learn := main.c

all : $(SYS)

linux : OS := LINUX
linux : CFLAGS += -I/usr/include/SDL2
linux : LDFLAGS += -L/usr/lib/i386-linux-gnu -lSDL2
linux : $(SDL_Learn) sdlLearn

macosx : OS := MACOSX
macosx : CFLAGS += -I/usr/local/include/SDL2
macosx : LDFLAGS += -L/usr/local/lib/i386-linux-gnu -lSDL2
macosx : $(SDL_Learn) sdlLearn

sdlLearn :
	$(cc) $(CFLAGS) -o $@ $(SDL_Learn) $(LDFLAGS)

clean :
	rm -f sdlLearn
