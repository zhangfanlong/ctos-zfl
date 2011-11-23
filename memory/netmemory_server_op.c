//nermemory_server.c
/*The netmemory server provides shared memory objects 
whose contents are maintained consistently when mapped by multiple hosts.


Warning:libmach.a
*/

//#include <>
#include <stdio.h>

int main(int argc, char *argv[])
{
	//netmemory_cache 
	/*Function ¡ª Create a Mach memory object from a netmemory object
	kern_return_t netmemory_cache(mach_por_t netmemory_server,
									mach_port_t netmenory_object,
									mach_port* memory_object);
	*/

	//netmenory-creat
	/*Function ¡ª Create a netmemory object
	kern_return_t netmemory_create(mach_port_t netmeory_server,
									vm_sizt_t object_size,
									mach_port_t* netmeory_object,
									mach_port_t* netmemory_contorl);
	*/
	
	//netmemory_destory
	/*Function ¡ª Destroy a netmemory object
	kern_return_t netmemory_destory(mach_port_t netmemory_control);
	*/

	//
	/*
	*/

	return 0;
}
