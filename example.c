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


// bubble 排序
void zencil_sort_triangle_points_by_y(
        int *x1, int *y1,
        int *x2, int *y2,
        int *x3, int *y3)
{
    // bubble sort 
    if(*y1 > *y2){
        ZENCIL_SWAP(int, *x1, *x2);
        ZENCIL_SWAP(int, *y1, *y2);
    }
    if(*y2 > *y3){
        ZENCIL_SWAP(int, *x2, *x3);
        ZENCIL_SWAP(int, *y2, *y3);
    }
    if(*y1 > *y2){
        ZENCIL_SWAP(int, *x1, *x2);
        ZENCIL_SWAP(int, *y1, *y2);
    }
}

// 绘制线段
bool zencil_line_of_segment(int x1, int y1,int x2,int y2, int *k,int *c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if(dx == 0) return false;
    *k = dy/dx;
    *c = y1 - dy*x1/dx;

    return true;
}

// 绘制三角形(三角形可以组成任意图形)
void zencil_fill_triangle(uint32_t *pixels, size_t width, size_t height,
        int x1, int y1,
        int x2, int y2,
        int x3, int y3,
        uint32_t color)
{
    //对于输入点进行按 y 进行排序
    zencil_sort_triangle_points_by_y(&x1,&y1,&x2,&y2,&x3,&y3);

    // 判断 3 个点是否能够组成一个三角形
    // p1p2 连线的斜率为 k12 截距为 c12
    int dx12 = x2 - x1;
    int dy12 = y2 - y1;
    int dx13 = x3 - x1;
    int dy13 = y3 - y1;

    for(int y = y1; y <=y2; y++){
        if( 0 <= y && (size_t)y < height){
            int s1 = dy12 != 0 ? (y - y1)*dx12/dy12 + x1:x1;
            int s2 = dy13 != 0 ? (y - y1)*dx13/dy13 + x1:x1;
            if(s1 > s2 ) ZENCIL_SWAP(int,s1,s2);
            for (int x = s1; x < s2; x++)
            {
                if( 0 <= x && (size_t)x < width){
                    pixels[y*width + x] = color;
                }
            }
        }
    }

    int dx32 = x2 - x3;
    int dy32 = y2 - y3;
    int dx31 = x1 - x3;
    int dy31 = y1 - y3;

    for(int y = y2; y <=y3; y++){
        if( 0 <= y && (size_t)y < height){
            int s1 = dy32 != 0 ? (y - y3)*dx32/dy32 + x3:x3;
            int s2 = dy31 != 0 ? (y - y3)*dx31/dy31 + x3:x3;
            if(s1 > s2 ) ZENCIL_SWAP(int,s1,s2);
            for (int x = s1; x < s2; x++)
            {
                if( 0 <= x && (size_t)x < width){
                    pixels[y*width + x] = color;
                }
            }
        }
    }
}



int main(int argc, char const *argv[])
{
    zencil_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);
    int radius = 10;

    uint32_t color = 0xFF00FF00;


    int x1 = WIDTH/2,y1 = HEIGHT/8;
    int x2 = WIDTH*4/8,y2 = HEIGHT/2;
    int x3 = WIDTH/8*7,y3 = HEIGHT/8*7;

    zencil_fill_circle(pixels,WIDTH,HEIGHT,
        x1,y1,radius,
        color);
    zencil_fill_circle(pixels,WIDTH,HEIGHT,
        x2,y2,radius,
        color);
    zencil_fill_circle(pixels,WIDTH,HEIGHT,
        x3,y3,radius,
        color);


    zencil_fill_triangle(pixels, WIDTH,HEIGHT,
        x1,y1,
        x2,y2,
        x3,y3,
        0xFFFFFF00);

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

