#include<stdio.h>
#include<stdint.h>
#include<errno.h>
#include<string.h>

#include "zencil.c"

// 定义输出图像的大小
#define WIDTH 800
#define HEIGHT 600

// 在 golang 语言结构，用于在函数返回之前执行一些代码，用于资源回收，日志记录，清理缓存
// defer 语句可以在函数多次使用，LIFO()
#define return_defer(value) do {result = (value); goto defer;} while(0)

static uint32_t pixels[WIDTH*HEIGHT];


// 对一张图像填充单色
// 函数是可以分为声明和定义
//声明(签名)，对函数一个描述，面向函数使用者，（函数名(标识符)，参数列表和返回值)
//定义(实现)，对函数一个实现，面向函数设计者
//可以多次声明，对于一个函数仅允许定义一次

//uint32_t 和 int 取值范围，u 无符号，int ，图像中，位置颜色也好通常不会考虑符号
//uint32_t 更适合这种场景

void zencil_fill(uint32_t *pixels, size_t width, size_t height,uint32_t color);
int zencil_save_to_ppm_file(uint32_t *pixels, size_t width ,size_t height, const char*file_path);
int main(void)
{
    printf("hello world");
    zencil_fill(pixels,WIDTH,HEIGHT,0xFF00FFFF);
    zencil_save_to_ppm_file(pixels,WIDTH,HEIGHT,"output_01.ppm");
    return 0;
}

typedef int Errno;

int zencil_save_to_ppm_file(uint32_t *pixels, size_t width ,size_t height, const char*file_path)
{
    // 打开文件
    int result = 0;
    FILE *f = NULL;
    {
        f = fopen(file_path,"wb");
        // errono 可以跟踪不同函数调用期间发生的
        //发生错误时，对应函数会将 errorno 设置非零值，表示错误类型

        // EACCES 拒绝访问
        // EEXIST 文件或目录已存在
        // EINVAL 无效参数
        // EIO    读写错误  
        if(f == NULL) return_defer(errno);
        // printf %zu 是格式化字符串，输出 size_t 类型变量占位符通常我们会选择 %zu
        fprintf(f,"P6\n%zu %zu 255\n",width,height);
        //golang 语言对于错误处理 defer ，
        if(ferror(f)) return_defer(errno);

        // 像素 [255,0,0]
        for(size_t i = 0; i < width*height; ++i)
        {
            //0xAABBGGRR
            uint32_t pixel = pixels[i];
            // 提取像素 [] 表示
            uint8_t bytes[3] = {
                (pixel>>(8*0))&0xFF,
                (pixel>>(8*1))&0xFF,
                (pixel>>(8*2))&0xFF,
            };

            // 适合二进制，根据指定大小来写入
            fwrite(bytes,sizeof(bytes),1,f);
            if(ferror(f)) return_defer(errno);
        }
    }

defer:
    if(f) fclose(f);
    return result;
}


// [0,0,0]
// [0,0,0]
// [0,0,0]
// [0,0,0]
// width=3 height=4 图像，接下来要为图像进行逐像素上色处理，单色图像

//[[0,0,0],[0,0,0],[0,0,0],[0,0,0]] height(函数) x width 矩阵

void zencil_fill(uint32_t *pixels, size_t width, size_t height,uint32_t color){
    // size_t 无符号的类型，c/c++ 
    for(size_t i = 0; i< width*height; ++i){
        pixels[i] = color;
    }

}
