//vm_map+vm_regionµÄÊ¾Àý³ÌÐò
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

