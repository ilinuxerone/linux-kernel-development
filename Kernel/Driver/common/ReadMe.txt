linux驱动程序编写基础
内核模块的优缺点
优点：
灵活， 修改内核时不必重新编译内核。
只需编译相应的模块，然后insmod将模块装载即可

缺点：
由于内核所占用的内存是不会被换出的，所以连接进内核的模块会给系统带来
一定的性能和内存利用方面的损失
内核要维护模块之间的依赖性

linux内核模块 与应用程序的区别
                C语言程序                   linux内核模块
运行		用户控件                     内核空间
入口             main()				module_init()
出口          	无                              module_exit()
编译           gcc -c                           Makefile
链接           ld                               insmod
运行          直接运行                          insmod
调试             gdb                            kdb  kgdb

static声明， 因为这种函数在特定文件之外没有其他意义
__init	该函数只在初始化期间使用，模块装载后，将该函数占用的内存空间释放
__exit 只用于模块卸载


导出符号表 
EXPOER_SYSMBOL(name);
EXPORT_SYSMBOL_GPL(name);
注意：符号表必须在文件的全局部分导出，不能再函数部分导出
cat /proc/kallsyms


