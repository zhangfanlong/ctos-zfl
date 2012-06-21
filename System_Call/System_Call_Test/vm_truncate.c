//vm_truncateµÄ²âÊÔ³ÌÐò
main.c:
#include <stdio.h>
#include <mach.h>
#include <sys/ctos_syscall.h>
#include <error.h>

int main()
{
	int err;
	char *buf ;
	err = vm_allocate(mach_task_self(), (vm_address_t *)&buf, 
			(vm_size_t)0x30000, TRUE);
	if (err)
		error(1, err, "vm_allocate 1");

	err = vm_truncate(mach_task_self(), (vm_address_t)buf, 
			(vm_size_t)0x10000);
	if (err)
		error (1, err, "vm_truncate");

	char *ptr = buf + 0x10000;
	err = vm_allocate(mach_task_self(), (vm_address_t *)&ptr,
			(vm_size_t)0x20000, FALSE);
	if (err)
		error(1, err, "vm_allocate 2");
	puts(¡°fine¡±);
	return 0;
}

/*
Makefile:
CFLAGS = -Wall
run:	main.c 
	gcc $(CFLAGS) -o $@ $^
clean:
	-rm run 
*/