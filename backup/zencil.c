#ifndef ZENCIL_C_
#define ZENCIL_C_
#include<stdio.h>
#include<stdint.h>
#include<errno.h>
#include<string.h>

#define return_defer(value) do {result = (value); goto defer;} while(0)

// void zencil_fill(uint32_t *pixels, size_t width, size_t height,uint32_t color);
// int zencil_save_to_ppm_file(uint32_t *pixels, size_t width ,size_t height, const char*file_path);

typedef int Errno;

int zencil_save_to_ppm_file(uint32_t *pixels, size_t width ,size_t height, const char*file_path)
{
    int result = 0;
    FILE *f = NULL;
    {
        f = fopen(file_path,"wb");

        if(f == NULL) return_defer(errno);
   
        fprintf(f,"P6\n%zu %zu 255\n",width,height);
        
        if(ferror(f)) return_defer(errno);

        for(size_t i = 0; i < width*height; ++i)
        {
            uint32_t pixel = pixels[i];
            uint8_t bytes[3] = {
                (pixel>>(8*0))&0xFF,
                (pixel>>(8*1))&0xFF,
                (pixel>>(8*2))&0xFF,
            };

            fwrite(bytes,sizeof(bytes),1,f);
            if(ferror(f)) return_defer(errno);
        }
    }

defer:
    if(f) fclose(f);
    return result;
}

void zencil_fill(uint32_t *pixels, size_t width, size_t height,uint32_t color){
    for(size_t i = 0; i< width*height; ++i){
        pixels[i] = color;
    }
}

void zencil_fill_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height, 
    int x0, int y0, size_t w, size_t h, 
    uint32_t color)
{
    for(int dy = 0; dy < (int)h; ++dy){
        int y = y0 + dy;
        // printf("y=%d\n",y);
        if(0<=y && y < (int)pixels_height){
            for(int dx = 0; dx < (int)w; ++dx){
                int x = x0 + dx;
                // printf("x=%d\n",x);
                if(0<=x && x < (int)pixels_width){
                    pixels[y*pixels_width + x] = color;
                }
            }
        }
    }
}

#endif//ZENCIL_C_