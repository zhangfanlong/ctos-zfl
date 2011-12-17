#include <stdio.h>
#include <mach.h>

/*
host=23;
*/
int main()
{
	host_t host;
	kern_return_t kr;
	host=mach_host_self();
	printf("%d\n",host);
}
