//netname_netmemory_shared2.c

/*怎样使用nameserver+memory_object进行内存共享--son.
该任务寻找存在的netmemory object，然后映射到自己的
虚拟地址空间中，然后读写数据。
*/

#include <mach.h>
#include <stdio.h>
#include <servers/netname.h>

int main(int argc, char *argv[])
{
	kern_return_t kr;
	mach_port_t netmemory_server;

	mach_port_t netmemory_object;
	mach_port_t memory_object;
	
	netname_name_t netmemory_object_name;
	vm_size_t size=vm_page_size;
	vm_address_t address;
	boolean_t anywhere=TRUE;


//
	kr=netname_look_up(name_server_port,
						"",
						"netmemoryserver",
						&netmemory_server);
	if (kr)
		return kr;

//
	kr=netname_look_up(name_server_port,"",
						netmemory_object_name,
						&netmemory_object);
		if (kr)
		{
			printf("netmemory is not find\n");
			return kr;
		}
	
//
	kr=netmemory_cache(netmemory_server,
						netmemory_object,
						&memory_object);
	if (kr)
		return kr;

//
	kr=vm_map(mach_task_self(),&address,size,0,anywhere,
					memory_object,0,FALSE,VM_PROT_DEFAULT,
					VM_PROT_DEFAULT,VM_INHERIT_SHARE);

	if (kr)
		return kr;

//
	printf("address is %d\n",address);
	//address=100;
	
	return 0;
}