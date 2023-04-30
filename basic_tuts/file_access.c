#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    FILE *fh_output;

    // w 表示写入
    // a 表示追加
    fh_output = fopen("file.txt","w");
    // do something 
    // fputs 只是支持字符串输入，没有 fprintf 格式化功能
    // 会有返回值负数或者 0 分别表示
    fputs("A string\n",fh_output);

    int data = 12;
    // fprintf 既可以写入字符串，也可以写入其他类型的数据
    fprintf(fh_output,"data:%d\n",data);
    fclose(fh_output);

    return 0;
}