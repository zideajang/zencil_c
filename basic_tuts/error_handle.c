#include<stdio.h>
#include<errno.h>
#include<string.h>

// 在 c 语言中 exter，告诉编译器这个变量可以跨文件来使用
// extern int errno;

int main(void)
{

    FILE *fh;
    fh = fopen("notfound.txt","r");
    if(fh == NULL){
        printf("Errno after:%d\n",errno);
        printf("Error msg");
        // 
        // printf("Error msg: %s\n",strerror(errno));
    }else fclose(fh);
    return 0;
}