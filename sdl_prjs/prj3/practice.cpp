#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gXOut = NULL;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("We have problem with initializing SDL. ERROR: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // create window
        gWindow = SDL_CreateWindow("SDL EXAMPLE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created. SDL_ERROR: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    gXOut = SDL_LoadBMP("x.bmp");
    if (gXOut == NULL)
    {
        printf("unable to load %s | SDL ERROR: %s\n", "x.bmp", SDL_GetError());
        success = false;
    }

    printf("Surface width: %d\n", gXOut->w);
    printf("Surface height: %d\n", gXOut->h);
    printf("Surface pitch: %d\n", gXOut->pitch);
    printf("Bits per pixel: %d\n", gXOut->format->BitsPerPixel);
    printf("Bytes per pixel: %d\n", gXOut->format->BytesPerPixel);

    return success;
}

void close()
{
    SDL_FreeSurface(gXOut);
    gXOut = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

int main(int argc, char *args[])
{
    if (!init())
    {
        printf("failed to initialize!\n");
    }
    else
    {

        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {

            bool quit = false;

            // Event Handler
            SDL_Event e;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                // Apply the image
                SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();

    return 0;
}