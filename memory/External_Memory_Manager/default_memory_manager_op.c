//default_memory_manager_op.c

/*
使用default memory manager的三个个接口，分别是设置管理器、创建临时对象、销毁临时对象。
*/

/*使用vm_set_default_memory_manager()
  失败,返回错误是:(os/kern) invalid host
	    kr值:kr=22
  使用memory_object_create(),memory_object_destroy()
  失败。返回错误都是：(ipc/send) invalid destination port.
	    kr值：kr=268435459
*/

#include<stdio.h>
#include<mach.h>

int main()
{
    memory_object_t new_memory_object;
	memory_object_control_t new_control;
	memory_object_name_t new_name;
	mach_port_t default_manger;
	default_manger=MACH_PORT_NULL;
	kern_return_t kr;
	kern_return_t reason=0;
	
	printf("mach_host-self() is %d\n",mach_host_self());
	
	kr=vm_set_default_memory_manager(mach_host_self(),
									 &default_manger);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("vm_set_default_memory_manager() is exiting:kr=%d\n",kr);
			return kr;
		}
	//printf("memory_object_init is ok\n");								 
	kr=memory_object_create(MEMORY_OBJECT_NULL,//MEMORY_OBJECT_NULL
							new_memory_object,
							vm_page_size,
							new_control,
							new_name,
							vm_page_size);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("memory_object_create() is exiting:kr=%d\n",kr);
			return kr;
		}
	//printf("memory_object_init is ok\n");
	
	/*kr=memory_object_data_initialize(new_memory_object,
									   new_control,
									   vm_offset_t offset,//
									   vm_offset_t data,//
									   vm_size_t data_count);//
	if(kr)
	{
		mach_error("the value of error is",kr);
		printf("memory_object_data_initialize() is exited.kr=%d\n",kr);
		return kr;
	}
	//printf("memory_object_data_initialize is ok\n");
	*/
	
	kr=memory_object_destroy(new_control,reason);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("memory_object_destroy() is exiting.kr=%d\n",kr);
			return kr;
		}
	//printf("every thing is ok,and main is exiting\n");

	
	return 0;
}