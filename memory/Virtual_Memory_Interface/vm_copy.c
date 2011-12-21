//vm_copy.c

/* 
 * This program is a test of vm_allocate, vm_copy and vm_deallocate.
 * First some memory is allocated, and filled with data.  
 * Another chunck of memory is allocated, and vm_copy is called to copy
 * the contents of the first chunk to the second.  The data of the two
 * spaces is compared to be sure it is the same, checking vm_copy.
 * vm_deallocate is then used to rid of the two chunks of memory.
 */

#include <mach.h>
#include <stdio.h>
#include <stdlib.h>

int main(argc, argv)
{
	vm_address_t data1,data2;
	int	i;
	kern_return_t	kr;

	if (argc > 1) {
		printf("vm_copy takes no switches.  ");
		printf("This program is an example vm_copy\n");
		exit(1);
	}

	kr=vm_allocate(mach_task_self(),&data1,vm_page_size,TRUE);
	if (kr!= KERN_SUCCESS) 
		{
			mach_error("vm_allocate returned value of ", kr);
			printf("vm_copy: Exiting.\n");
			exit(1);
		}

	for (i = 0; (i < vm_page_size / sizeof(vm_address_t)); i++) 
		{
			(&data1)[i] = i;
			//printf("%d\n",(&data1)[i]);
		}	
	printf("vm_copy: set data\n");
	kr=vm_protect(mach_task_self(),data1,vm_page_size,FALSE,VM_PROT_READ|VM_PROT_WRITE);
	kr=vm_protect(mach_task_self(),data2,vm_page_size,FALSE,VM_PROT_READ|VM_PROT_WRITE);

	kr= vm_allocate(mach_task_self(),&data2,vm_page_size,TRUE);
	if (kr!= KERN_SUCCESS)
		{
			mach_error("vm_allocate returned value of ", kr);
			printf("vm_copy: Exiting.\n");
			exit(1);
		}

	kr=vm_copy(mach_task_self(),data1,vm_page_size,data2);
	if (kr!= KERN_SUCCESS)
		{
			mach_error("vm_copy returned value of ", kr);
			printf("vm_copy: Exiting.\n");
			exit(1);
		}
	printf("vm_copy: copied data\n");

	for (i = 0; (i < vm_page_size / sizeof(vm_address_t)); i++)
		{
			if ((&data1)[i] != (&data2)[i])
				{
					printf("vm_copy: Data not copied correctly.\n");
					printf("vm_copy: Exiting.\n");
					exit(1);
				}
		}
		
	printf("vm_copy: Successful vm_copy.\n");

	kr=vm_deallocate(mach_task_self(),data1,vm_page_size);
	if(kr!= KERN_SUCCESS)
		{
			mach_error("vm_deallocate returned value of ", kr);
			printf("vm_copy: Exiting.\n");
			exit(1);
		}

	kr=vm_deallocate(mach_task_self(),data2,vm_page_size);
	if(kr!= KERN_SUCCESS)
		{
			mach_error("vm_deallocate returned value of ", kr);
			printf("vm_copy: Exiting.\n");
			exit(1);
		}
	
	printf("vm_copy: Finished successfully!\n");
}