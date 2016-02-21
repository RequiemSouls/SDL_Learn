#include <stdbool.h>
#include <stdio.h>
#include "SDL.h"

bool sh_init();
bool sh_loadMedia();
SDL_Surface* loadSurface(char* path);
void sh_close();

int SCREEN_WIDTH = 400;
int SCREEN_HEIGHT = 300;

enum KeyPressSurface
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface* gKeySurface[KEY_PRESS_SURFACE_TOTAL];
//The window we'll rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gCurrentSurface = NULL;
int main(int argc, char* args[])
{
    bool quit = false;
    SDL_Event e;
    //Start up SDL and create window
    if (!sh_init())
    {
        printf("Failed to load initialize!\n");
    }
    else
    {
        //Load media
        if (!sh_loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            gCurrentSurface = gKeySurface[KEY_PRESS_SURFACE_DEFAULT];
            while (!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            gCurrentSurface = gKeySurface[KEY_PRESS_SURFACE_UP];
                            break;
                        case SDLK_DOWN:
                            gCurrentSurface = gKeySurface[KEY_PRESS_SURFACE_DOWN];
                            break;
                        case SDLK_LEFT:
                            gCurrentSurface = gKeySurface[KEY_PRESS_SURFACE_LEFT];
                            break;
                        case SDLK_RIGHT:
                            gCurrentSurface = gKeySurface[KEY_PRESS_SURFACE_RIGHT];
                            break;
                        default:
                            gCurrentSurface = gKeySurface[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                //Apply the image
                SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
                //Wait two seconds;
                SDL_Delay(16);
            }
        }
    }

    //Free resources and close SDL
    sh_close();

    return 0;
}

bool sh_init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //create window
        gWindow = SDL_CreateWindow( "SDL Learn", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool sh_loadMedia()
{
    //Load splash image
    gKeySurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("assert/press.bmp");
    gKeySurface[KEY_PRESS_SURFACE_UP] = loadSurface("assert/up.bmp");
    gKeySurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("assert/down.bmp");
    gKeySurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("assert/left.bmp");
    gKeySurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assert/right.bmp");
    if (gKeySurface[KEY_PRESS_SURFACE_DEFAULT] == NULL
        || gKeySurface[KEY_PRESS_SURFACE_UP] == NULL
        || gKeySurface[KEY_PRESS_SURFACE_DOWN] == NULL
        || gKeySurface[KEY_PRESS_SURFACE_LEFT] == NULL
        || gKeySurface[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        printf("Failed to load image!");
        return false;
    }
    return true;
}

SDL_Surface* loadSurface(char* path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }

    return loadedSurface;
}

void sh_close()
{
    for (int surfaceIndex = 0;
             surfaceIndex < KEY_PRESS_SURFACE_TOTAL; surfaceIndex++)
    {
        SDL_FreeSurface(gKeySurface[surfaceIndex]);
        gKeySurface[surfaceIndex] = NULL;
    }

    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    SDL_Quit();
}