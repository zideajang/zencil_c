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
static uint32_t actual_pixels[WIDTH*HEIGHT];

// 0xAABBGGRR 分解为 4 个通道
int main(int argc, char const *argv[])
{
    // 图像填充背景颜色
    zencil_fill(actual_pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);
    // 绘制两个重叠效果用于演示通道混合效果
    zencil_fill_rect(actual_pixels,WIDTH,HEIGHT,
        0,0,WIDTH*3/4,HEIGHT*3/4,0xFF0000FF);
    zencil_fill_rect(actual_pixels,WIDTH,HEIGHT,
        WIDTH/4,HEIGHT/4,WIDTH,HEIGHT,0x5500FF00);

    zencil_fill_circle(actual_pixels,WIDTH,HEIGHT,WIDTH/2,HEIGHT/2,WIDTH/3,0x55FF2020);

    int x1 = WIDTH/2,y1 = HEIGHT/8;
    int x2 = WIDTH*4/8,y2 = HEIGHT/2;
    int x3 = WIDTH/8*7,y3 = HEIGHT/8*7;

    zencil_fill_triangle(actual_pixels, WIDTH,HEIGHT,
            0,HEIGHT,
            WIDTH,HEIGHT,
            WIDTH/2,0,
            0xBB20AAAA);

    const char *file_path = "alpha_example_5.ppm";
    
    Errno err = zencil_save_to_ppm_file(actual_pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return 1;
    }
    return 0;
    
}

