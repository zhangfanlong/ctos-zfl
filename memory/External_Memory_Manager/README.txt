这里是关于内存操作和内存共享的例子，正在做。
（1）gun_external_memory_op.c，是全部接口的索引以及使用。

（2）default_memory_manager.c，是default_memory_manager默认内存管理的三个接口的使用。
     三个接口是更改memory manager，使用新的memory manager创建、初始化、销毁内存对象（memory object）。

（3）memory_object_init.c，是使用memory_object_init（）以及memory_object_destroy（）的使用。

（4）memory_object_mmap.c，是即将使用mmap和memory object实现的内存共享。