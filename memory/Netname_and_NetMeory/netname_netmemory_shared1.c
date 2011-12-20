//����ʹ��nameserver+memory_object�����ڴ湲��
/*�����񴴽�netmemory object�����ҷ�����netname server��
����ӳ�䵽�Լ��������ڴ�ռ��У�Ȼ��д���ݡ�


*/

#include <mach.h>
#include <stdio.h>
#include <servers/netname.h>

int main(int argc, char *argv[])
{
	kern_return_t kr;
	mach_port_t netmemory_server;

	mach_port_t netmemory_object;
	mach_port_t netmemory_control;
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
	kr=netmemory_create(netmemory_server,
						size,
						&netmemory_object,
						&netmemory_control);
	if (kr)
		return kr;

//
	kr=netname_checkin(name_server_port,
					   netmemory_object_name,
					   MACH_PORT_NULL,
					   netmemory_object);
	if (kr)
		return kr;

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
	address=100;

//		
	while(1)
		;


	return 0;
}
