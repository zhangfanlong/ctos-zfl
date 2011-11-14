/* 
 * This program is a test of vm_allocate, vm_copy and vm_deallocate.
 * First some memory is allocated, and filled with data.  
 * Another chunck of memory is allocated, and vm_copy is called to copy
 * the contents of the first chunk to the second.  The data of the two
 * spaces is compared to be sure it is the same, checking vm_copy.
 * vm_deallocate is then used to rid of the two chunks of memory.
 *
 *************************************************************/

#include <mach_init.h>
#include <mach.h>
#include <stdio.h>

main(argc, argv)
	int	argc;
	char	*argv[];
{
	int		*data1, *data2, *temp;
	int		i;
	kern_return_t	rtn;

	if (argc > 1) {
		printf("vm_copy takes no switches.  ");
		printf("This program is an example vm_copy\n");
		exit();
	}

	if ((rtn = vm_allocate(task_self(), &data1, 
		vm_page_size, TRUE)) != KERN_SUCCESS) {
		mach_error("vm_allocate returned value of ", rtn);
		printf("vm_copy: Exiting.\n");
		exit();
	}

	temp = data1;
	for (i = 0; (i < vm_page_size / sizeof(int)); i++) 
		temp[i] = i;
	printf("vm_copy: set data\n");

	if ((rtn = vm_allocate(task_self(), &data2, 
		vm_page_size, TRUE)) != KERN_SUCCESS) {
		mach_error("vm_allocate returned value of ", rtn);
		printf("vm_copy: Exiting.\n");
		exit();
	}

	if ((rtn = vm_copy(task_self(), data1, vm_page_size,
		data2)) != KERN_SUCCESS) {
		mach_error("vm_copy returned value of ", rtn);
		printf("vm_copy: Exiting.\n");
		exit();
	}
	printf("vm_copy: copied data\n");

	for (i = 0; (i < vm_page_size / sizeof(int)); i++) {
		if (data1[i] != data2[i]) {
			printf("vm_copy: Data not copied correctly.\n");
			printf("vm_copy: Exiting.\n");
			exit();
		}
	}
	printf("vm_copy: Successful vm_copy.\n");

	if ((rtn = vm_deallocate(task_self(), data1, 
		vm_page_size)) != KERN_SUCCESS) {
		mach_error("vm_deallocate returned value of ", rtn);
		printf("vm_copy: Exiting.\n");
		exit();
	}

	if ((rtn = vm_deallocate(task_self(), data2, 
		vm_page_size)) != KERN_SUCCESS) {
		mach_error("vm_deallocate returned value of ", rtn);
		printf("vm_copy: Exiting.\n");
		exit();
	}
	printf("vm_copy: Finished successfully!\n");
}