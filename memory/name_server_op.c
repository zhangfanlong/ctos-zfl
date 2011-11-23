//name_server_op.c 
/*是关于name server的一些操作，这个服务是：snames。
The name server provides a registry mapping service names to 
ports attached to the servers providing the named service.

labmach.c
#include <servers/netname.h>

netname_look_up();
netname_check_in();
netname_check_out();
netname_version();
*/

#include <servers/netname.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	//netname_check_in();
	/*Register a server
	kern_return_t netname_check_in(mach_port_t server_port,
									netname_name_t port_name,
									mach_port_t signature,
									mach_port_t port_id);
*/
	

	//netname_check_out();
	/*De-register a server

	kern_return_t netname_check_out(mach_port_t server_port,
									netname_name_t port_name,
									mach_name_t signature);
	*/

	//netname_look_up();
	/*Return a port to a named server

	kern_return_t netname_look_up(mach_name_t server_port,
									netname_name_t host_name,
									netname_name_t port_name,
									mach_port_t* port_id);
	*/

	//netname_version();
	/*Return a version string describing the name server
	kern_return_t netnamt_version(mach_port_t name_server,
									netname_name_t port_name);
	*/

	return 0;
}
