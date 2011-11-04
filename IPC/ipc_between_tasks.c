/*The first sample program shows how to pass messages between two tasks. 
This is a good illustration of the following fundamental Mach features:
allocation, deallocation, and use of ports; use of the Environment Manager; 
setting up message structures; 
and communication between two processes via messages on ports. 
 
In this example the parent task will fork a child task, 
which will send the parent a message containing data.
The parent will then notify the child that he received the data by sending a reply message.*/

/*
//print the error information
kern_return_t error;
mach_error("PARENT: port_allocate returned value of",error);*/

/*
//Port Allocation
port_t result;
kern_return_t error;
if(error=(port_allocate(task_self(),&result))!=KERN_SUCESS)
{
	mach_error("PARENT: port_allocate returned value of",error);
	exit(1);
}
*/

/*
//port deallocation
kern_return_t error;
port_t my_port;
if(reeor=port_deallocate(task_self(),my_port)!=KERN_SUCCESS)
{
	mach_error("PARENT: port_deallocate returned value of",error);
	exit(1);
}
*/

/*
//Environment Manager Server/Checking in a Port
env_name_t name; 
port_t comm_port; 
kern_return_t error;
if ((error = env_set_port(environment_port, name, comm_port)) != KERN_SUCCESS) 
{
	mach_error("PARENT: env_set_port returned value of ", error); 
	exit(1);
}
*/

/*
//Environment Manager Server/looking up in a Port
env_name_t name;
port_t comm_port;
kern_return_t error;
/* Name has been previously set to a desired string. */
if ((error = env_get_port(environment_port, name, &comm_port)) != KERN_SUCCESS) 
{
	mach_error("env_get_port returned ", error);
	exit(1);
}
*/
