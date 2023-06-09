# 从头学着用 c 语言实现一个图像处理库 
## 名字由来
pencil - replace p with z zencil

## ppm 文件格式为
```
p6
width height
body
```
ppm 文件格式为


## 相关基础知识
### 函数声明和定义

函数是可以分为声明和定义
- 声明(签名)，对函数一个描述，面向函数使用者，（函数名(标识符)，参数列表和返回值)
- 定义(实现)，对函数一个实现，面向函数设计者，
- 声明和定义区别: 可以多次声明，对于一个函数仅允许定义一次

### 数据类型 uint32_t 和 int 区别
uint32_t 和 int 取值范围，u 无符号，int ，图像中，位置颜色也好通常不会考虑符号，uint32_t 更适合这种场景

### errorno 使用
errono 可以跟踪不同函数调用期间发生的，发生错误时，对应函数会将 errorno 设置非零值，表示错误类型
- EACCES 拒绝访问
- EEXIST 文件或目录已存在
- EINVAL 无效参数
- EIO    读写错误  

### 通过宏来实现类似 golang 语言对于错误处理 defer 
在 golang 语言结构，用于在函数返回之前执行一些代码，用于资源回收，日志记录，清理缓存，defer 语句可以在函数多次使用，LIFO()

```c 
#define return_defer(value) do {result = (value); goto defer;} while(0)
```

### 图像格式定义
在这里采用1 维数组来定义图像

```
[0,0,0]
[0,0,0]
[0,0,0]
[0,0,0]
width=3 height=4 图像，接下来要为图像进行逐像素上色处理，单色图像

[[0,0,0],[0,0,0],[0,0,0],[0,0,0]] height(函数) x width 矩阵
```

### TODO
- 矩形位置