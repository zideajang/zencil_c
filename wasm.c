#include "zencil.c"

#define WIDTH 800
#define HEIGHT 600

uint32_t pixels[WIDTH * HEIGHT];

uint32_t *render(void)
{
    zencil_fill(pixels,WIDTH,HEIGHT,0xFF202020);

    int x1 = WIDTH/2,y1 = HEIGHT/8;
    int x2 = WIDTH*4/8,y2 = HEIGHT/2;
    int x3 = WIDTH/8*7,y3 = HEIGHT/8*7;

     zencil_fill_triangle(pixels, WIDTH,HEIGHT,
            x1,y1,
            x2,y2,
            x3,y3,
            0xFFFFFF00);

    return pixels;
}