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


// 绘制矩形
void zencil_fill_rect(uint32_t *pixels,size_t pixels_width,size_t pixels_height, 
    int x0,int y0, size_t w, size_t h,uint32_t color )
{
    for (int dy = 0; dy < (int)h; dy++)
    {
        int y = y0 + dy;//row
        if(0 <= y && y < (int)pixels_height){
            for (int dx = 0; dx < (int)w; dx++)
            {
                int x = x0 + dx;
                if(0 <= x && x < (int)pixels_width){
                    pixels[y*pixels_width + x] = color;
                }
            }
        }
        
    }
    
}

int main(int argc, char const *argv[])
{
    zencil_fill(pixels,WIDTH,HEIGHT,0xFF202020);

    zencil_fill_rect(pixels,WIDTH,HEIGHT,0,0,100,50,0xFF2020FF);

    const char *file_path = "output.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return 1;
    }
    return 0;
    
}

