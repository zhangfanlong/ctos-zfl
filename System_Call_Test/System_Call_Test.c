//shm_open+mmap的示例程序
main.c:
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int fd = shm_open("test", O_RDWR|O_CREAT, S_IRWXU);
	if (fd < 0) {
		perror("shm_open() failed.");
		exit(1);
	}

	ftruncate(fd, 1024);//Bus error occuring without this line.

	char *buf;
	buf = mmap(0, 1024, PROT_READ|PROT_WRITE, 
				MAP_SHARED|MAP_32BIT, fd, 0);
	if (buf) 
		sprintf(buf, "good");
	else
		perror("mmap() failed.");
	return 0;
}
/*Makefile：
run:	main.c
	gcc -o $@ $< -lrt
clean:
	-rm test.s test.i
*/

	
//vm_map+vm_region的示例程序
main.c:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mach.h>
#include <error.h>

int main ()
{
	char * buf = (char *)malloc(4096);
	sprintf(buf, "good");
	char * ptr = buf;
	vm_size_t size;
	vm_prot_t protection;
	vm_prot_t max_protection;
	vm_inherit_t inheritance;
	boolean_t shared;
	mach_port_t object_name;
	vm_offset_t offset;
	int err;
	err = vm_region(mach_task_self(), (vm_address_t *)&ptr,
			&size, &protection, &max_protection,
			&inheritance, &shared, &object_name,
			&offset);
	if (err)
		error(1, err, "vm_region");

	char * shadow;
	err = vm_map(	mach_task_self(), 
			(vm_address_t *)&shadow,
			4096,
			0,
			TRUE,
			object_name, //NULL,
			offset,
			FALSE,
			protection,
			max_protection,
			inheritance);
	if (err)
		error(1, err, "vm_map");
	if (shadow) {
		strcat(shadow, " fine");
		puts(shadow);
	}
	else
		puts("shadow = NULL");
	return 0;
}

/*
Makefile:
CFLAGS = -Wall -lmachuser
run:	main.c 
	gcc $(CFLAGS) -o $@ $^
clean:
	-rm run 
*/

//vm_truncate的测试程序
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
	puts(“fine”);
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