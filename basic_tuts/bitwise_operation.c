#include<stdio.h>
#include<stdlib.h>

void print_binary(unsigned int num)
{
    while (num)
    {
        if(num & 1)
            printf("1");
        else
            printf("0");

        num >>=1;
    }

    printf("\n");
    
}

int main(void)
{
    // 关键字(int) 关键字(int) x(标识符) 赋值操作符 字面量
    // 9 0000 1001 >> :100100
    // 7654 3210
    // 128 64 32  16 8421
    //100100 4 + 32 = 36
    unsigned int x = 9;
    
    // 12 0000 1100
    unsigned int y = 12;

    unsigned int r;

    r = x << 2;
    char buffer[33];

    itoa(r,buffer,2);
    printf("binary:%s\n",buffer);
    printf("r = %d\n",r);
    // print_binary(y);
    


}