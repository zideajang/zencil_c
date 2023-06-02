#ifndef ZENCIL_H_
#define ZENCIL_H_
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


#endif //ZENCIL_H_