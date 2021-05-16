#include <assert.h>
#include "yuv.h"

Uint8 meep(Uint8 b, Uint8 g, Uint8 r)
{
  int res = (int)((float)r * 0.299 + (float)g * 0.587 + (float)b * 0.114);

  return (Sint8) (res - 127);
}


void bgr24_to_luma(SDL_Surface *bgr, Sint8 *luma)
{
    assert(bgr->format->format == SDL_PIXELFORMAT_BGR24);
    Uint8 *pixels = bgr->pixels;

    for (int y = 0; y < bgr->h; y += 1)
    {
        for (int x = 0; x < bgr->w; x += 1)
        {
            size_t bgr_offset = (bgr->pitch * y) + (x * 3);
            size_t luma_offset = y * bgr->w + x;
            luma[luma_offset] = meep(pixels[bgr_offset], pixels[bgr_offset+1], pixels[bgr_offset+2]);
        }
     }
}