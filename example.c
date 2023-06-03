#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<error.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

#include "zencil.c"

// 绘制图像画布的大小
#define WIDTH 800
#define HEIGHT 600

// 定*2义
#define COLS (8*2)
#define ROWS (6*2)

#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define BACKGROUND_COLOR 0xFF202020
#define FOREGROUND_COLOR 0xFF2020FF

static uint32_t pixels[WIDTH*HEIGHT];


void swap_int(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void zencil_draw_line(uint32_t *pixels, size_t pixels_width, size_t pixels_height,
    int x1,int y1,int x2,int y2,
    uint32_t color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if(dx != 0) {
        // float k = (float)dy/(float)dx;
        float c = y1 - dy*x1/dx;

        if(x1 > x2) swap_int(&x1, &x2); 
        for(int x = x1; x <= x2; x++){

            if(0 <= x && x < (int)pixels_width){
                int nx = x + 1;
            
                int sy1 = dy*x/dx + c;
                int sy2 = dy*(x + 1)/dx + c; 
                if(sy1 > sy2) swap_int(&sy1,&sy2);
                for(int y = sy1; y <= sy2; y++ ){
                    if(0 <= y && y < (int)pixels_height){
                        pixels[y*pixels_width + x] = color;
                    }
                }
            }
        }
    }else{
        int x = x1;
        if(0 <= x && x < pixels_width){
            if(y1 < y2) swap_int(&y1,&y2);
            for(int y = y1; y <= y2; y++){
                if(0 <= y && y < pixels_height){
                    pixels[y*pixels_width + x] = color;
                }
            }
        }
    }
}

bool lines_example(void)
{
    zencil_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);

    zencil_draw_line(pixels,WIDTH,HEIGHT,
    0,0,WIDTH/4,HEIGHT,FOREGROUND_COLOR);

    zencil_draw_line(pixels,WIDTH,HEIGHT,
    WIDTH,0,WIDTH/4*3,HEIGHT,FOREGROUND_COLOR);

    const char *file_path = "lines_example.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return false;
    }
    return true;
}

bool checkboard_example(void){

    zencil_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);

    for(int y =0; y < ROWS; y++ ){
        for (int x = 0; x < COLS; x++)
        {
            uint32_t color = BACKGROUND_COLOR;
            if((x + y)%2 ==0){
                color = FOREGROUND_COLOR;
            }
            zencil_fill_rect(pixels,WIDTH,HEIGHT,x*CELL_WIDTH,y*CELL_HEIGHT,CELL_WIDTH,CELL_HEIGHT,color);
        }
        
    }

    const char *file_path = "checkboard_example.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return false;
    }

    return true;
}

float lerpf(float a, float b, float c){
    return a + (b-a)*c;
}

// 工作分解
// 分层 层之间是协议沟通
bool circle_example(void)
{
    zencil_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);

    for(int y =0; y < ROWS; y++ ){
        for (int x = 0; x < COLS; x++)
        {
            uint32_t color = FOREGROUND_COLOR;
            
            float u = (float) x/COLS;
            float v = (float) y/ROWS;
            float t = (u+v)/2;
            // radius 可以看作直径
            size_t radius = CELL_WIDTH;
            // u = x/COLS 也就是 x(0,COLS)/COLS (0,1)
            // v = y/ROWS y in (0,1) 取值范围为 0 到 1 之间的数
            // t = (u  + v)/2 (0,2)  t (0,1) 
            // 出现数在 p 是一个(0,1)之间的小数 ，px1 + (1-p)x2


            // lerp(radius/2,radius,t);(t-1)radius/2 + radius*t
            // float u = (float)x/COLS
            
            if(CELL_HEIGHT < radius) radius = CELL_HEIGHT;
            
            zencil_fill_circle(pixels,WIDTH,HEIGHT,x*CELL_WIDTH + CELL_WIDTH/2,
                y*CELL_HEIGHT + CELL_HEIGHT/2,(size_t)lerpf(radius/8,radius/2,t),FOREGROUND_COLOR);
        }
        
    }


    const char *file_path = "circle_example.ppm";
    
    Errno err = zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,file_path);
    
    if(err){
        fprintf(stderr,"ERROR: could not save file:%s: %s\n",file_path);
        return false;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    // if(!checkboard_example()) return -1;
    // if(!circle_example()) return -1;

    if(!lines_example()) return -1;
    return 0;
    
}

