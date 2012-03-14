//memory_object_init.c

/*
主动显示调用memory_object_init（）以及memory_object_destroy（）函数。
*/

/*使用memory_object_init（）以及memory_object_destroy（）
  失败。
  返回错误都是：(ipc/send) invalid destination port.
	      kr值：kr=268435459
 失败原因：
	[自己分析]memory_object_init（）是不可以显示调用的，应该是由内核调用的。
	内存对象压根就没有建立，销毁是也是不可能完成的工作了，所以也会出错。
    使用vm_map（）进行试验看看。
*/

#include<stdio.h>
#include<mach.h>

int main()
{
    memory_object_t memory_object;
	memory_object_control_t memory_control;
	memory_object_name_t memory_object_name;
	
	kern_return_t kr;
	kern_return_t reason;

	kr=memory_object_init(memory_object,memory_control,
						  memory_object_name, vm_page_size);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("memory_object_init() is exiting:%d\n",kr);
			return kr;
		}
	printf("memory_object_init is ok\n");

	kr=memory_object_destroy(memory_control,reason);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("memory_object_destroy() is exiting.kr=%d\n",kr);
			//return kr;
		}
	//printf("every thing is ok,and main is exiting\n");

	
	return 0;
}