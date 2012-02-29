/*memory_object_mmap.c
使用mmap和memory object实现的内存共享
*/


#include <mach.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	//定义变量并初始化
	kern_return_t kr;
	vm_task_t target_task;
	vm_address_t *address=NULL;
	vm_size_t size=vm_page_size;
	vm_address_t mask;
	boolean_t anywhere=TURE;
	memory_object_t memory_object;
	vm_offset_t offset=0;
	boolean_t copy=FALSE;
	vm_prot_t cur_protection=;
	vm_prot_t max_protection=;
	vm_inherit_t inheritance=;

	kr=0;

	kr=vm_map(target_task,*address,size,mask,anywhere,
				memory_object,offset,copy,cur_protection,
				max_protection, inheritance);
				
	

}