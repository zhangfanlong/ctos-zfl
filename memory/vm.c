/*vm.c 简单的操作内存区域例子
************************************************************
*/

#include <mach.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char ** argv)
{
	vm_address_t data1;
	vm_address_t data2;

	int data_cnt,i,min;
	kern_return_t rtn;


//vm-allcate
	rtn=vm_allocate(mach_task_self(),&data1,vm_page_size,TRUE);
	if (rtn!= KERN_SUCCESS) 
		{
			mach_error("vm_allocate returned value of ", rtn);
			printf("Exiting.\n"); 
			exit(0);
		}
	printf("vm_allocate data1 is ok\n"); 

	rtn=vm_allocate(mach_task_self(),&data2,vm_page_size,TRUE);
	if (rtn!= KERN_SUCCESS) 
		{
			mach_error("vm_allocate returned value of ", rtn);
			printf("Exiting.\n"); 
			exit(0);
		}
	printf("vm_allocate data2 is ok\n"); 
	//输出4096

	printf("vm_page_size is %d\n",vm_page_size);
    
	printf("write data1\n");
	for(i=0;i<vm_page_size;i++)
	{
		(&data1)[i]=i;
	}
	/*
	printf("read data1\n");
	for(i=0;i<vm_page_size;i++)
	{
		printf("data1 shu ju wei %d\n",(&data1)[i]);
	}
	*/
//vm_copy 在同一个任务中;

	rtn=vm_copy(mach_task_self(),data1,vm_page_size,data2);
	if (rtn!= KERN_SUCCESS) 
		{
			mach_error("vm_copy returned value of ", rtn);
			printf("Exiting.\n"); 
			exit(0);
		}
	printf("vm_copy is ok\n");
	printf("read data2\n");
	for(i=0;i<vm_page_size;i++)
	{
		printf("data2 shu ju wei %d\n",(&data2)[i]);
	}


//vm_inherit 设置新的属性
/*
kern_return_t vm_inherit (mach_port_t target_task,
	vm_address_t address,
	vm_size_t size,
    vm_inherit_t new_inheritance);
*/

//设置机器属性，实现pmap的机制
/*vm_machine_attribute
Sets and gets special attributes of a memory region
SYNOPSIS
kern_return_t vm_machine_attribute (
				mach_port_t target_task,
				vm_address_t address,
				vm_size_t size,
				vm_machine_attribute_t attribute,
				vm_machine_attribute_val_t* value);
*/

//vm_map最重要的函数啊，使用它完成不同任务之间的内存共享
/**/


//vm_protect 设置访问属性
/**/
	
//vm_read 可以在不同的任务中;
/*	rtn = vm_read(mach_task_self(), *data1, vm_page_size, data2, &data_cnt);
	if (rtn!= KERN_SUCCESS) 
		{
			mach_error("vm_read returned value of ", rtn); 
			printf("vmread: Exiting.\n");
			exit(0);
		}
	printf("Successful vm_read.\n");
*/

//vm_write
/**/

//vm_region内存区域的属性
/**/

//vm_statistics内核所知的属性
/**/

//vm_wire
/**/

//vm_write在不同的任务之间也可以

//vm_deallcate;	
	rtn = vm_deallocate(mach_task_self(), data1, vm_page_size);
	if (rtn!= KERN_SUCCESS) 
				{
					mach_error("vm_deallocate returned value of ", rtn);
					printf("vmread: Exiting.\n"); 
					exit(0);
				}
	printf("vm_deallcate data1 is ok !\n");
	rtn = vm_deallocate(mach_task_self(), data2, vm_page_size);
	if (rtn!= KERN_SUCCESS) 
				{
					mach_error("vm_deallocate returned value of ", rtn);
					printf("vmread: Exiting.\n"); 
					exit(0);
				}
	printf("vm_deallcate data2 is ok !\n");
	
	return 0;
}


