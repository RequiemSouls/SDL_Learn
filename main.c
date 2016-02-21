#include <stdbool.h>
#include <stdio.h>
#include "SDL.h"

bool sh_init();
bool sh_loadMedia();
void sh_close();

int SCREEN_WIDTH = 400;
int SCREEN_HEIGHT = 300;

//The window we'll rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
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
        if (!hz_loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            while (!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
                //Apply the image
                SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
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
    //Loading success flag
    bool success = true;

    //Load splash image
    char* imgPath = "assert/preview.bmp";
    gHelloWorld = SDL_LoadBMP(imgPath);
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", imgPath, SDL_GetError());
        success = false;
    }
    return success;
}

void sh_close()
{
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    SDL_Quit();
}