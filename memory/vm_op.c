/*vm.c 简单的操作内存区域例子
************************************************************
This chapter discusses the specifics of the kernel’s virtual memory interfaces. 
This includes memory status related functions associated with a single task. 
************************************************************
*/

#include <mach.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char ** argv)
{
	/*define something
	vm_address_t data1;
	vm_address_t data2;
	vm_offset_t data3;

	int data_cnt,i,min;
	kern_return_t kr;
	*/

//vm_allcate():Function — Allocates a region of virtual memory
/*kern_return_t vm_allocate(vm_task_t(or mach_port_t) target_task, 
							vm_address_t *address, 
							vm_size_t size, 
							boolean_t anywhere)
*/
/*kr=vm_allocate(mach_task_self(),&data1,vm_page_size,TRUE);
	if (kr!= KERN_SUCCESS) 
		{
			mach_error("vm_allocate returned value of ", kr);
			printf("Exiting.\n"); 
			exit(0);
		}
	printf("vm_allocate data1 is ok\n"); 

	kr=vm_allocate(mach_task_self(),&data2,vm_page_size,TRUE);
	if (kr!= KERN_SUCCESS) 
		{
			mach_error("vm_allocate returned value of ", kr);
			printf("Exiting.\n"); 
			exit(0);
		}
	printf("vm_allocate data2 is ok\n"); 
	//输出4096

	printf("vm_page_size is %d\n",vm_page_size);
    //write data1
	
	printf("init data1\n");
	for(i=0;i<1024;i++)
	{
		(&data1)[i]=i;
	}
*/
	/*
	printf("printf data1\n");
	for(i=0;i<1024;i++)
	{
		printf("data1 shu ju wei %d\n",(&data1)[i]);
	}
	*/


//vm_copy:Function — Copies a region in a task’s virtual memory(在同一个任务中);
/*
kern_return_t vm_copy(mach_port_t target_task,
					  vm_address_t source_address,
					  vm_size_t count,
					  vm_address_t dest_address);
*/

/*	kr=vm_copy(mach_task_self(),data1,vm_page_size,data2);
	if (kr!= KERN_SUCCESS) 
		{
			mach_error("vm_copy returned value of ", kr);
			printf("Exiting.\n"); 
			exit(0);
		}
	printf("vm_copy is ok\n");
*/
	/*
	printf("printf data2\n");
	for(i=0;i<1024;i++)
	{
		printf("data2 shu ju wei %d\n",(&data2)[i]);
	}
	*/


//vm_deallcate():Function — De-allocates a region of virtual memory
/*kern_return_t vm_deallocate(mach_port_t target_task,
							  vm_address_t address,
							  vm_size_t size);
使用见后面
*/

//vm_inherit():Sets the inheritance attribute for a region of virtual memory
//设置继承属性
/*
kern_return_t vm_inherit(mach_port_t target_task,
						 vm_address_t address,
						 vm_size_t size,
						 vm_inherit_t new_inheritance);
*/


//*vm_machine_attribute():Sets and gets special attributes of a memory region
//SYNOPSIS设置机器属性，实现pmap的机制(我觉得暂时用不上）
/*
kern_return_t vm_machine_attribute (
				mach_port_t target_task,
				vm_address_t address,
				vm_size_t size,
				vm_machine_attribute_t attribute,
				vm_machine_attribute_val_t* value);
*/


//vm_map():Function — Maps a memory object to a task’s address space
//最重要的函数啊，使用它完成不同任务之间的内存共享
/*
kern_return_t vm_map(mach_port_t target_task,
					 vm_address_t* address,
					 vm_size_t size,
					 vm_address_t mask,
					 boolean anywhere,
					 mach_port_t memory_object,
					 vm_offset_t offset
					 boolean copy,
					 vm_port_t cur_protection,
					 vm_port_t max_protection,
					 vm_inherit_t inhertance);
*/


//vm_protect():Sets access privileges for a region of virtual memory
//设置访问属性
/*
kern_return_t vm_protect(mach_port_t target_task,
						 vm_address_t address,
						 vm_size_t size,
						 boolean_t set_maximum,
						 vm_port_t new_protection);
vm_port_t new_protection:
	VM_PROT_READ--Allows read access.
	VM_PROT_WRITE--Allows write access.
	VM_PROT_EXECUTE--Allows execute access.

*/
	

//vm_read():Function — Reads a task’s virtual memory 
//可以在不同的任务中;
/*
kern_return_t vm_read(mach_port_t target_task,
					  vm_address address,
					  vm_size_t size,
					  vm_offset* data,
					  mach_msg_type_number_t* data_count);
vm_offset_t data:
*/

/*	kr = vm_read(mach_task_self(), data1, vm_page_size, &data3, &data_cnt);
	if (kr!= KERN_SUCCESS) 
		{
			mach_error("vm_read returned value of ", kr); 
			printf("vmread: Exiting.\n");
			exit(0);
		}
	printf("Successful vm_read.\n");
	printf("read data3\n");
	for(i=0;i<vm_page_size;i++)
	{
		printf("data3 shu ju wei %d\n",(&data3)[i]);
	}
*/
//vm_region():Returns information on a region of virtual memory
/*
kern_return_t vm_region(mach_port_t target_mask,
						vm_address_t* address,
						vm_size_t* size,
						vm_port_t* protection,
						vm_port_t* max_protection,
						vm_inherit_t* inheritance,
						boolean_t* shared,
						mach_port_t* object_name,
						vm_offset_t* offset);

*/

//vm_statistics:Returns statistics on the kernel’s use of virtual memory
/*
kern_return_t vm_statistics (mach_port_t target_task,
							vm_statistics_data_t* vm_stats);
*/
/*	kern_return_t kr;
	vm_statistics_data_t vm_statas;
	kr=vm_statistics(mach_task_self(),&vm_statas);
	if(kr)
		{
			return kr;
			mach_error(kr);
		}
	printf("the pagesie is %ld\n",vm_statas.pagesize);
*/

//vm_wire:Specifies the pageability of a region of virtual memory
/*
kern_return_t vm_wire(mach_port_t host_priv, 
					  mach_port_t target_task,
					  vm_address_t address,
					  vm_size_t size,
					  vm_prot_t wired_access);
*/

//vm_write():Writes data to a task’s virtual memory
/*
kern_return_t vm_write(mach_port_t target_task,
					   vm_address_t address,
					   vm_offset_t data,
					   mach_msg_type_number_t data_count);
*/


//vm_deallocate
/*	kr = vm_deallocate(mach_task_self(), data1, vm_page_size);
	if (kr!= KERN_SUCCESS) 
				{
					mach_error("vm_deallocate returned value of ", kr);
					printf("vmread: Exiting.\n"); 
					exit(0);
				}
	printf("vm_deallcate data1 is ok !\n");
	kr = vm_deallocate(mach_task_self(), data2, vm_page_size);
	if (kr!= KERN_SUCCESS) 
				{
					mach_error("vm_deallocate returned value of ", kr);
					printf("vmread: Exiting.\n"); 
					exit(0);
				}
	printf("vm_deallcate data2 is ok !\n");
	
	//data3
	kr = vm_deallocate(mach_task_self(), data3, vm_page_size);
	if (kr!= KERN_SUCCESS) 
				{
					mach_error("vm_deallocate returned value of ", kr);
					printf("vmread: Exiting.\n"); 
					exit(0);
				}
	printf("vm_deallcate data3 is ok !\n");
*/	
	return 0;
}