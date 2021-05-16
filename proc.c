#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL.h>
#include "yuv.h"
#include "vdbg.h"

typedef enum operation_e { ENCODE, DECODE } operation;

void usage(char *bin)
{
    printf("usage: %s <encode.bmp> | <show.mew>\n", bin);
    exit(1);
}

void err_msg(char *msg)
{
    printf("%s", msg);
    exit(1);
}

bool str_endswith(const char *str, const char* end)
{
    size_t str_len = strlen(str);
    size_t end_len = strlen(end);
    if (str_len < end_len)
    {
        return false;
    }

    int res = strncmp(&str[(str_len - end_len)], end, end_len);
    return res == 0;
}

void parse_args(int argc, char *argv[], char **file_name, operation* op)
{
    if (argc != 2)
    {
        usage(argv[0]);
    }

    *file_name = argv[1];
    if (str_endswith(*file_name, ".bmp"))
    {
        *op = ENCODE;
        return;
    }

    if (str_endswith(*file_name, ".mew"))
    {
        *op = DECODE;
        return;
    }

    printf("unexpected file type '%s'\n", *file_name);
    usage(argv[0]);
}

void encode_bmp(char *file_name)
{
    SDL_Surface *image = SDL_LoadBMP(file_name);
    if (image == NULL)
    {
       err_msg("error loading BMP file\n");
    }
    Sint8 *luma_image = malloc(image->w * image->h);

    bgr24_to_luma(image, luma_image);
    show_img(luma_image, image->w, image->h);
}

int main(int argc, char *argv[])
{
    char *file_name;
    operation op;

    parse_args(argc, argv, &file_name, &op);

    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    switch (op)
    {
        case ENCODE:
            encode_bmp(file_name);
            break;
        case DECODE:
            printf("decode\n");
            break;
    }
}