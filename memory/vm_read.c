/*vm_read.c �򵥵Ĳ����ڴ���������
�����ã������кܴ������
��������ָ���ĵ��е�����
/* *
* This program is a test of vm_allocate, vm_read and vm_deallocate. 
* First some memory is allocated, and filled with data. vm_read is 
* then called, with reading starting at the previously allocated chunk. 
* The contents of the two pieces of memory, one retreived by vm_allocate, and
* one by vm_read is compared. vm_deallocate is then used to rid of the 
* two chunks of memory. *
************************************************************
*/

#include <mach.h>
#include <stdio.h>
#include <stdlib.h>

void main(int argc,char ** argv)
{
	vm_address_t *data1,*temp;
	vm_address_t *data2;
	int data_cnt,i,min;
	kern_return_t rtn;


	if ((rtn = vm_allocate(mach_task_self(), data1, vm_page_size, TRUE)) != KERN_SUCCESS) 
		{
			mach_error("vm_allocate returned value of ", rtn);
			printf("vmread: Exiting.\n"); 
			exit(0);
		}
		else
			{
				printf("vm_allocate data1 is ok\n"); 
			}

	printf("will fill space allocated with some data.\n");
	//�����⣬�޷�д��
	for(i=0;i<vm_page_size;i++)
		printf("hehe");
		data1[i]=i;
	printf("Filled space allocated with some data.\n");
	
	printf("Doing vm_read....\n");
	//�����⣬�޷�����
	if ((rtn = vm_read(mach_task_self(), *data1, vm_page_size, data2, &data_cnt)) != KERN_SUCCESS) 
		{
			mach_error("vm_read returned value of ", rtn); 
			printf("vmread: Exiting.\n");
			exit(0);
		}
		printf("Successful vm_read.\n");

		if (vm_page_size != data_cnt) 
			{
				printf("vmread: Number of bytes read not equal to number");
				printf("available and requested. \n");
			}
		
		min=(vm_page_size<data_cnt)?data_cnt:vm_page_size;

		for(i=0;(i<min);i++)
			{
				if (data1[i]!=data2[i])
				{
					printf("vmread: Data not read correctly.\n"); 
					printf("vmread: Exiting.\n"); 
					exit(0);
				}
			}

			printf("Checked data successfully.\n");

			if ((rtn = vm_deallocate(mach_task_self(), *data1, vm_page_size)) != KERN_SUCCESS) 
				{
					mach_error("vm_deallocate returned value of ", rtn);
					printf("vmread: Exiting.\n"); 
					exit(0);
				}
			if ((rtn = vm_deallocate(mach_task_self(), *data2, data_cnt)) != KERN_SUCCESS) 
				{
					mach_error("vm_deallocate returned value of ", rtn);
					printf("vmread: Exiting.\n");
					exit(0);
				}
				
}

