/*The following is a routine which demonstrates 
how to use the netmemory server.
解释了怎样使用netmemory server完成内存共享
*/

#include <servers/netname.h>


/*create and map a shared object of given size with netname object_name
创建并且map一个共享对象，给定了大小和netname object_name*/

/*One task (the “master”) should call this routine with hostname = 0; the routine
will then create a netmemory object and register it with the netname server
under the supplied object name. All other tasks (the “slaves”) call this routine
with the hostname where the master lives.
*/
kern_return_t map_object(char* object_name,char* hostname,
						vm_offset_t* address,vm_size_t size,
						boolean_t anywhere)
{
	kern_return_t kr;
	mach_port_t netmemory_server;
	mach_port_t memory_object;
	mach_port_t netmemory_object;
	mach_port_t netmemory_control;

/*Find the local netmemory server. (If this routine is used a lot, this value
can be cached.)
找到本地主机的netmemory server
*/
	kr=netname_look_up(name_server_port,"","netmemoryserver",&netmemory_server);
	if(kr)
		return kr;

/*If a hostname is provided, then we are the slave and thus we simply
look up the netmemory object on the given host by using the object
name. If a hostname is not provided, then we are the master and thus
have the responsibility of creating a netmemory object and registering
it with the netname service under the given object name.
*/
	if(hostname)
	{
		kr=netname_look_up(name_server_port,hostname,
							object_name,
							&netmemory_object);
		if (kr)
			return kr;	
	}
	else
	{
		kr=netmemory_create(netmemory_server,
							size,
							&netmemory_object,
							&netmemory_control);
		if (kr)
			return kr;

		kr=netname_checkin(name_server_port,
							object_name,
							MACH_PORT_NULL,
							netmemory_object);
		if (kr)
		{
			kr=netmemory_destory(netmemory_control);
			return kr;
		}
	}

/*Cache the object locally. Note that even the master must do this.
*/
	kr=netmemory_cache(netmemory_server,
						netmemory_object,
						&memory_object);
	if (kr)
	{
		return kr;
	}

/*Map the object, either anywhere or at the supplied address.
*/
	if (anywhere)
	{
		*address=0;
		//set address

		kr=vm_map(mach_task_self(),address,size,0,anywhere,
					memory_object,0,FALSE,VM_PROT_DEFAULT,
					VM_PROT_DEFAULT,VM_INHERIT_SHARE);
		//处理内容

		if (kr)
		{
			return kr;
		}

		return KERN_SUCCESS;
	}
}