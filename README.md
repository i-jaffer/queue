# Readme

## Feature

这是一个用 c 语言实现的队列，具有以下特点：

+ 使用简单
+ 支持定义多个队列，相互之间不冲突
+ 出入对操作具有锁保护
+ 支持预出队机制

## Compiler

Linux.

##  Usage

1. 输入`make ` 编译工程
2. 输入`make lib`编译生成对应动态库和静态库
3. 输入`make clean` 清除工程
4. 默认使用`gcc` 编译，如果需要使用其他编译器编译，在`make` 时需设置编译器参数，如`make CC=aarch64-linux-gun-gcc` 
5. 编译不同平台的库时，需要先使用`make` 编译对应的`.o` 文件，之后使用`make lib` 生成对应的 `lib` 库，不可直接使用 `make lib`生成对应的库

## License

The license is MIT.

Author is wanglei.