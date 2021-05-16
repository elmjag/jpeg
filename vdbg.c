#include <stdbool.h>
#include "vdbg.h"

#define SCALE 32

static void wait_for_quit_event()
{
    SDL_Event event;
    bool run = true;
    while (run)
    {
        if (SDL_WaitEvent(&event) != 1)
        {
            printf("error in SDL_WaitEvent\n");
            run = false;
        }
        if (event.type == SDL_QUIT)
        {
           run = false;
        }

    }
}

static void draw_image(Sint8 *image, SDL_Surface *surface, int w, int h)
{
    Uint8 *pixels = surface->pixels;
    for (int y = 0; y < h; y += 1)
    {
        for (int x = 0; x < w; x += 1)
        {
            Uint8 pix_val = image[y*w+x] + 127;
            int offset = (surface->pitch * y) + (x*3);

            pixels[offset+0] = pix_val;
            pixels[offset+1] = pix_val;
            pixels[offset+2] = pix_val;
        }
    }
}

void show_two_8x8_img(Sint8 *left, Sint8 *right)
{
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    SDL_Window *window =
        SDL_CreateWindow("8x8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         8*SCALE*2 + 10, 8*SCALE, SDL_WINDOW_SHOWN);

    SDL_Surface *windowsurface = SDL_GetWindowSurface(window);
    SDL_Surface *surface =
        SDL_CreateRGBSurfaceWithFormat(0, 8, 8, 32, SDL_PIXELFORMAT_RGB24);

    /* left */
    draw_image(left, surface, 8, 8);
    SDL_Rect dest = {.x = 0, .y = 0, .w = 8*SCALE, .h = 8*SCALE};
    SDL_BlitScaled(surface, NULL, windowsurface, &dest);

    /* right */
    draw_image(right, surface, 8, 8);
    SDL_Rect dest2 = {.x = 8*SCALE + 10, .y = 0, .w = 8*SCALE, .h = 8*SCALE};
    SDL_BlitScaled(surface, NULL, windowsurface, &dest2);

    SDL_UpdateWindowSurface(window);
    wait_for_quit_event();
    SDL_DestroyWindow(window);
}

void show_8x8_img(Sint8 *image)
{
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    SDL_Window *window =
        SDL_CreateWindow("8x8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         8*SCALE, 8*SCALE, SDL_WINDOW_SHOWN);

    SDL_Surface *surface =
        SDL_CreateRGBSurfaceWithFormat(0, 8, 8, 32, SDL_PIXELFORMAT_RGB24);
    draw_image(image, surface, 8, 8);

    SDL_Surface *windowsurface = SDL_GetWindowSurface(window);

    SDL_Rect dest = {.x = 0, .y = 0, .w = 8*SCALE, .h = 8*SCALE};
    SDL_BlitScaled(surface, NULL, windowsurface, &dest);
    SDL_UpdateWindowSurface(window);

    wait_for_quit_event();
    SDL_DestroyWindow(window);
}

void show_img(Sint8 *image, int w, int h)
{
    SDL_Window *window =
        SDL_CreateWindow("luma", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         w, h, SDL_WINDOW_SHOWN);

    SDL_Surface *surface =
        SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGB24);
    draw_image(image, surface, w, h);

    SDL_Surface *win_surface = SDL_GetWindowSurface(window);

    SDL_BlitSurface(surface, NULL, win_surface, NULL);
    SDL_UpdateWindowSurface(window);

    SDL_FreeSurface(surface);
    wait_for_quit_event();
    SDL_DestroyWindow(window);
}

void print_f_img(float *img, int dim)
{
  for (int y = 0; y < dim; y += 1)
  {
    for (int x = 0; x < dim; x += 1)
    {
        printf("%f ", img[y*dim+x]);
    }
    printf("\n");
  }
}

void print_img(Sint8 *img, int dim)
{
  for (int y = 0; y < dim; y += 1)
  {
    for (int x = 0; x < dim; x += 1)
    {
        printf("%d ", img[y*8+x]);
    }
    printf("\n");
  }
}