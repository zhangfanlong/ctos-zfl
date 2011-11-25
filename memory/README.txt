这里是关于内存操作和内存共享的例子，正在做。
（1）vm.c是一些虚拟内存的基本操作
（2）vm_read.c是一个例子关于read内存的，不是很好用，但是思路是对的。
（3）vm_copy.c是另一个，同（2）。
（4）name_server_op.c是name_server的操作。//incoming
（5）netmemory_server_op.c是netmemory server的操作。//incoming
（6）map_object.c是使用（4）（5）进行内存共享的一个函数
（7）memory_share.c是内存共享的例子。//没做
（8）vm_address_t_and_vm_offset_t.c是关于vm_address_t_and_vm_offset_t的测试例子，确定这俩类型是什么。