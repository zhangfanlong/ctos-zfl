这个文件夹下是一些关于Mach ipc的例子。
    （1）bootstrap_ipc.c、receive_integer.c和send_intenger.c是一个例子，bootstrap_ipc.c是一个完整的程序，可以单独运行。receive_integer.c和send_intenger.c是接收和发送消息的函数，bootstrap_ipc.c中已经包括了后两者。
     bootstrap_ipc_rename.c和bootstrap_ipc_qlimit.c是对bootstrap_ipc.c扩展。
    （2）cthread_hello.c是线程的一个简单例子：。
    （3）ipc_hello.c同样是一个ipc的例子，使用到了（1）（2）的内容。
    （4）ipc_between_task.c也是ipc的例子。这个例子有很大问题，不能用。但是所提到的注册port有参考意义。