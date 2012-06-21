这里是关于内存操作和内存共享的例子。
（1）External_Memory_Manager是使用外部内存管理的接口。这里将实现内存共享。
（2）Virtual_Memory_Interface是使用虚拟内存接口。对于内存的基本操作函数。
（3）Netname_and_NetMeory是使用Netname和Netmempry的例子，不可以使用。
（4）mach_self.c是获得基本信息的代码。使用mach_task_self()获得task信息。
     使用mach_host_self()获得host信息。