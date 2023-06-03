#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<error.h>
#include<string.h>

#include "zencil.c"

// 绘制图像画布的大小
#define WIDTH 800
#define HEIGHT 600


// 定义
static uint32_t pixels[WIDTH*HEIGHT];
#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)


int main(int argc, char const *argv[])
{
    zencil_fill(pixels,WIDTH,HEIGHT,0xFF202020);

    for(int y =0; y < ROWS; y++ ){
        for (int x = 0; x < COLS; x++)
        {
            uint32_t color;
            if((x + y)%2 ==0){
                color = 0xFF0000FF;
            }else{
                color = 0xFF00FF00;
            }
            zencil_fill_rect(pixels,WIDTH,HEIGHT,x*CELL_WIDTH,y*CELL_HEIGHT,CELL_WIDTH,CELL_HEIGHT,color);
        }
        
    }


    const char *file_path = "output2.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return 1;
    }
    return 0;
    
}

