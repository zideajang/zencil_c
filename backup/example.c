#include<stdio.h>
#include<stdint.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>

#include "zencil.c"

#define WIDTH 800
#define HEIGHT 600


#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define BACKGROUND_COLOR 0xFF202020
#define FOREGRAOUND_COLOR 0xFF2020FF

static uint32_t pixels[WIDTH*HEIGHT];


void zencil_fill_circle(uint32_t *pixels, size_t pixels_width, size_t pixels_height,
    int cx, int cy, int r,
    uint32_t color)
{
    int x1 = cx - r;
    int y1 = cy - r;

    int x2 = cx + r;
    int y2 = cy + r;
    // zidejang
    for(int y = y1; y <= y2; ++y){
        if( 0 <= y && y < (int)pixels_height){
            for(int x = x1; x <= x2; ++x){
                 if( 0 <= x && x < (int)pixels_width){
                    int dx = x - cx;
                    int dy = y - cy;
                    if((dx*dx + dy*dy) <= r*r){
                        pixels[y*pixels_width + x]  = color;
                    }
                 }
            }

        }
    }

}

bool checker_example(void)
{
    zencil_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);

    size_t rw = 50;
    size_t rh = 50;

    for(int y = 0; y <ROWS; ++ y){
        for(int x = 0; x <COLS; ++ x){
            uint32_t color;
            if((x + y)%2 == 0){
                color = 0xFF0000FF;
            }else{

                color = BACKGROUND_COLOR;
            }
            zencil_fill_rect(pixels,WIDTH,HEIGHT,x*CELL_WIDTH,y*CELL_HEIGHT,CELL_WIDTH,CELL_HEIGHT,color);
        }
    }

    const char *file_path = "checkboard.ppm";
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR:could not save file %s:%s",file_path,strerror(errno));
        return false;
    }

    return true;

}

bool circle_exmaple(void)
{
    zencil_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);
    for(int y = 0; y < ROWS; ++ y){
        for(int x = 0; x < COLS;++x){
            int radius = CELL_WIDTH;
            if(CELL_HEIGHT < radius) radius = CELL_HEIGHT;
            zencil_fill_circle(pixels,WIDTH,HEIGHT, 
            x*CELL_WIDTH + CELL_WIDTH/2,y* CELL_HEIGHT + CELL_HEIGHT/2,radius/2,FOREGRAOUND_COLOR);
        }
    }
    const char *file_path = "circle.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR:could not save file %s:%s",file_path,strerror(errno));
        return false;
    }

    return true;

}


int main(void){

    if(!checker_example()) return -1;
    if(!circle_exmaple()) return -1;
    return 0;
}


