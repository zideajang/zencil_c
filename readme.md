## 手写 C 语言图形库—zencil

## 引言
最近每一个项目都写开头，就放下了，原因很多，其中一个原因还是个人的能力的局限性。其实并没有放下，还需要学习，所谓学习并不是抄袭，而是不断复现大佬的代码，然后多问自己为什么，就一些知识点进行展开。大家都希望看到一个完整地项目，而且也希望看到优雅代码，巧妙的设计。这些对于自己的确是一个调整。我会不断完善自己，细化和完善文档。希望对大家有益项目。

，

### 适合人群
- 对 c 语言有一定基础，有关编程经验
- 对数学要求并不高，具有一定逻辑性即可
- 想在编程路上走得更扎实的朋友

### 目标
- 实现一个图形库的项目
- 了解关于图像操作和处理一些背后原理
### 思路

### 引用
- 参考一个老外的项目和他教学视频
- 估计还会参考

### 相关项目
- 即将推出 SDL2
- 即将推出 SDL2 基本图形库
- 以及计划中基于 SDL2 的 simple 游戏引擎

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
