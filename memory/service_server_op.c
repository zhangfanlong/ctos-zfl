/*serveice server
The service server provides a registry for the service server itself, 
the name server and the environment server. 
It exists so that the ports for these servers can be created 
at system initialization while the servers themselves are initialized later.

//libmach.a 
//#include <servers/service.h>
*/


#include <servers/service.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

	//service_checkin
	/*Function ¡ª Announce the presence of a base Mach server
	kern_return_t service_waitfor (mach_port_t service_request,
									mach_port_t service_desired,
									mach_port_t service_granted);
	*/

	//service_waitfor
	/*Function ¡ª Wait for a base Mach server to be registered
	kern_return_t service_waitfor (mach_port_t service_request,
									mach_port_t service_desired);
	*/
	printf("Hello, world\n");
	return 0;
}
