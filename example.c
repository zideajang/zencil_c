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

// 0xAAGGBBRR 分解为 4 个通道
typedef enum 
{
    COMP_RED = 0,
    COMP_GREEN,
    COMP_BLUE,
    COMP_ALPHA,
    COUNT_COMPS,
} Comp_Index;



void unpack_rgb32(uint32_t c, uint8_t comp[COUNT_COMPS])
{
    for (size_t i = 0; i < COUNT_COMPS; i++)
    {

        comp[i] = c&0xFF;
        c >>=8;
    }
    
}
uint8_t zencil_mix_comps(uint8_t c1,uint8_t c2, uint8_t a)
{
    // 混合效果大于 255
    return c1 + (c2 - c1)*a/255;
}

uint32_t zencil_mix_colors(uint32_t c1, uint32_t c2)
{

    uint32_t comp1[COUNT_COMPS];
    unpack_rgb32(c1,comp1);

    uint32_t comp2[COUNT_COMPS];
    unpack_rgb32(c2,comp2);

    // lerp(comp1[COMP_RED])

    // lerp(a,b,t) = a + (b-a)*t
    // components are 0..255 instead of 0..1
    // a + (b - a )t 做插值混合运算

    // comp2[COMP_ALPHA]/255 取值范围变为 0..1
    // r1 + (r2 - r1)*a1/255


}

int main(int argc, char const *argv[])
{
    // 填充背景颜色
    zencil_fill(actual_pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);
    // 绘制两个重叠的
    // 绘制矩形
    zencil_fill_rect(actual_pixels,WIDTH,HEIGHT,
        0,0,WIDTH*3/4,HEIGHT*3/4,0xFF0000FF);
    // 绘制矩形
    zencil_fill_rect(actual_pixels,WIDTH,HEIGHT,
        WIDTH/4,HEIGHT/4,WIDTH*3/4,HEIGHT*3/4,0xFF00FFFF);
   

    const char *file_path = "alpha_example_2.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return 1;
    }
    return 0;
    
}

