#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<error.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<assert.h>
#include "zencil.c"

#define WIDTH 800
#define HEIGHT 600

#define BACKGROUND_COLOR 0xFF202020
#define FOREGROUND_COLOR 0xFF2020FF

static uint32_t pixels[WIDTH*HEIGHT];


// 今天将要实现透明效果



int main(int argc, char const *argv[])
{
    zencil_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);
    int radius = 10;

    uint32_t color = 0xFF00FF00;

    {
        int x1 = WIDTH/2,y1 = HEIGHT/8;
        int x2 = WIDTH*4/8,y2 = HEIGHT/2;
        int x3 = WIDTH/8*7,y3 = HEIGHT/8*7;

        // zencil_fill_circle(pixels,WIDTH,HEIGHT,
        //     x1,y1,radius,
        //     color);
        // zencil_fill_circle(pixels,WIDTH,HEIGHT,
        //     x2,y2,radius,
        //     color);
        // zencil_fill_circle(pixels,WIDTH,HEIGHT,
        //     x3,y3,radius,
        //     color);


        zencil_fill_triangle(pixels, WIDTH,HEIGHT,
            x1,y1,
            x2,y2,
            x3,y3,
            0xFFFFFF00);

    }

    {
        int x1 = WIDTH/2,y1 = HEIGHT/8;
        int x2 = WIDTH*4/8,y2 = HEIGHT/2;
        int x3 = WIDTH/8*7,y3 = HEIGHT/2;

        // zencil_fill_circle(pixels,WIDTH,HEIGHT,
        //     x1,y1,radius,
        //     color);
        // zencil_fill_circle(pixels,WIDTH,HEIGHT,
        //     x2,y2,radius,
        //     color);
        // zencil_fill_circle(pixels,WIDTH,HEIGHT,
        //     x3,y3,radius,
        //     color);


        zencil_fill_triangle(pixels, WIDTH,HEIGHT,
            x1,y1,
            x2,y2,
            x3,y3,
            0xFFFF00FF);

    }

    const char *file_path = "triangle_example_2.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return 1;
    }

    // int x1 = 69, y1 = 1;
    // int x2 = 12, y2 = 3;
    // int x3 = 128, y3 = 2;
    // printf("x1 = %d,y1 = %d\n",x1,y1);
    // printf("x2 = %d,y2 = %d\n",x2,y2);
    // printf("x3 = %d,y3 = %d\n",x3,y3);

    // zencil_sort_triangle_points_by_y(&x1,&y1,&x2,&y2,&x3,&y3);
    // printf("\n");
    // printf("x1 = %d,y1 = %d\n",x1,y1);
    // printf("x2 = %d,y2 = %d\n",x2,y2);
    // printf("x3 = %d,y3 = %d\n",x3,y3);

    return 0;
    
}

