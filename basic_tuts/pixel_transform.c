#include<stdio.h>
#include<stdint.h>

int main(void)
{
    uint32_t x = 0xFF00FFFF;

    // printf("%o",x);

    uint8_t bytes[3] = {
                (x>>(8*0))&0xFF,
                (x>>(8*1))&0xFF,
                (x>>(8*2))&0xFF,
            };

    printf("%d\n",bytes[0]);
    printf("%d\n",bytes[1]);
    printf("%d\n",bytes[2]);
    printf("%d\n",bytes[3]);

    return 0;
}