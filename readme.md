## 手写 C 语言图形库—zencil

- 创建 zencil.c 文件，关于绘制代码都放到这个文件
```c
#ifndef ZENCIL_H_
#define ZENCIL_H_


#endif //ZENCIL_H_
```


```c
#include<stdio.h>
#include<stdlib.h>

#include "zencil.c"

int main(void)
{

}
```

ppm 图像
```
P6
800 600
255
图像数据
```

关于 defer 这个现代语言特性在 c 语言实现

首先定义一个 defer 标识符，我们希望在退出函数前执行到 defer
在这里对一些资源进行释放
```c
defer:
    fclose(f);
```
我们在函数定义返回值的变量，因为这样做的好处就是
会在goto defer 前更改返回值
```c
if(f == NULL){
    result =-1;
    goto defer;
} 
```
通过定义宏
```c
#define return_defer(value) do {result=(value);goto defer;} while(0)
```