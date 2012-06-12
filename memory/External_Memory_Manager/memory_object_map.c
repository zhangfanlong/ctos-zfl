/*
memory_object_mmap.c
使用mmap和memory object实现的内存共享
*/

/*使用vm_map()创建新的内存对象，并对其进行一系列的操作尝试。
主要使用memory object内存对象相关的接口。
*/

#include <mach.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	//定义变量并初始化
	kern_return_t kr;
	vm_task_t target_task=mach_task_self();
	vm_address_t *address=NULL;
	vm_size_t size=vm_page_size;
	vm_address_t mask;//mask不会设置；
	boolean_t anywhere=TURE;
	memory_object_t memory_object=MEMORY_OBJECT_NULL;
	vm_offset_t offset=0;
	boolean_t copy=FALSE;
	vm_prot_t cur_protection=(VM_PORT_READ|VM_PORT_WRITE);//当前保护属性，读写
	vm_prot_t max_protection=(VM_PORT_READ|VM_PORT_WRITE);//最大保护属性，读写
	vm_inherit_t inheritance=VM_INHERIT_SHARE;//共享，设置共享

	kr=0;

	//建立一个新的内存对象，使用vm_map()；
	kr=vm_map(target_task,*address,size,mask,anywhere,
				memory_object,offset,copy,cur_protection,
				max_protection, inheritance);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("vm_map() is exiting:%d\n",kr);
			return kr;
		}
	printf("vm_map is ok\n");
	

}