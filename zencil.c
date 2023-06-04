#ifndef ZENCIL_H_
#define ZENCIL_H_


#define ZENCIL_SWAP(T,a,b) do{T t = a; a =b; b = t;} while(0)
#define ZENCIL_SIGN(T,x) ((T)((x) > 0) - (T)((x) < 0) )
#define zencil_abs(T,x) (ZENCIL_SIGN(T,x)*(x))


typedef int Errno;
// 1,2,3,4,5,6 ,width 2 height 3 

void zencil_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for (size_t i = 0; i < width*height; i++)
    {
        pixels[i] = color;
    }

    
}

#define return_defer(value) do {result=(value);goto defer;} while(0)

Errno zencil_save_to_ppm_file(uint32_t *pixels, size_t width ,size_t height, const char*file_path)
{
    int result = 0;
    FILE *f = NULL;
    {
        // 打开文件
        f = fopen(file_path,"wb");
        
        if(f == NULL) return_defer(errno);
        
        // 读取文件
        fprintf(f,"P6\n%zu %zu 255\n",width,height);

        if(ferror(f)) return_defer(errno);

        for(size_t i =0; i < width*height; i++){
            // 0xAARRGGBB
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

void zencil_fill_circle(uint32_t *pixels, 
    size_t pixels_width, size_t pixels_height, 
    int cx, int cy,int r, uint32_t color)
{
    // cx cy circle 位于范围内
    // (lefttop) x1,y1 rightbottom(x2,y2)
    // x1 < x < x2, y1 < y < y2
    int x1 = cx - (int) r;
    int y1 = cy - (int) r;

    int x2 = cx + (int) r;
    int y2 = cy + (int) r;
    for (int y = y1; y < y2; y++)
    {
        // 对 y 限制在图像区域内(row)
        if(0 <= y && y < pixels_height){

            for (int x = x1; x < x2; x++)
            {
                if(0<=x && x < pixels_width){
                    int dx =  x - cx;
                    int dy =  y - cy;
                    if(sqrt(dx*dx + dy*dy) <= r){
                        // printf("dx=%d",dx);
                        pixels[y*pixels_width + x] = color;
                    }
                }
            }
        }
    }
}

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

#endif //ZENCIL_H_