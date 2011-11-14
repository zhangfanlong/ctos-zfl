/* 
 * This program is an illustration of MACH message passing from a child
 * to the parent process and back.  In this example, the child is passing
 * a simple message where the data is stored in the message. The program 
 * allocates a port to use for communication.  The environment manager 
 * is used to register the port with a name that both the parent 
 * and child know. The program forks a child process which
 * then uses env_get_port to acquire the port needed for communication.
 * A message, containing the data the parent needs, is formed by the child 
 * and sent with msg_rpc to the parent.  msg_rpc does a send and a receive
 * using the same message buffer.  The parent does a receive on the
 * established communication port receiving the message from the child.
 * Upon receiving the child's message, the parent constructs and sends
 * a confirmation or reply message back to the child indicating he received
 * the child's message and data.  The call to msg_rpc by the child
 * receives the parent's reply.  The child then tells the environment
 * manager the communication port is no longer needed, and calls
 * port_deallocate.
 *
 **********************************************************/

#include <stdio.h>
#include <mach.h>
#include <mach_error.h>
#include <mach/message.h>
#include <servers/env_mgr.h>

#define	MAXDATA	20

/*  simple message structure */
struct simp_msg_struct {
	msg_header_t	h;
	msg_type_t	t;
	int		inline_data[MAXDATA];
};



/* This routine is used to set up the message containing the data that
 * the child will send to the parent.  Here the data is a simple array of
 * integers.  */

void setup_simp_request(msg_xmt, my_port)
	struct simp_msg_struct	*msg_xmt;
	port_t		my_port;

{
	int i;

	msg_xmt->h.msg_local_port = thread_reply();
	msg_xmt->h.msg_remote_port = my_port;
	msg_xmt->h.msg_size = sizeof(struct simp_msg_struct);
	msg_xmt->h.msg_id = 0x12345678;
	msg_xmt->h.msg_type = MSG_TYPE_NORMAL;
	msg_xmt->h.msg_simple = TRUE;

	msg_xmt->t.msg_type_name = MSG_TYPE_INTEGER_32;
	msg_xmt->t.msg_type_size = 32;
	msg_xmt->t.msg_type_number = MAXDATA;
	msg_xmt->t.msg_type_inline = TRUE;
	msg_xmt->t.msg_type_longform = FALSE;
	msg_xmt->t.msg_type_deallocate = FALSE;
	for (i = 0; i < MAXDATA; i++)
		msg_xmt->inline_data[i] = i;

}


/* This procedure is used to set up the reply message that the parent is
 * sending to the child.  Note that the remote_port of the received message 
 * designates where the reply message will be sent. No data is sent in this
 * message, so the size of the message is simply the size of the message
 * header.  */

void setup_simp_reply(msg_xmt, msg_rcv)
	msg_header_t		*msg_xmt;
	struct simp_msg_struct	*msg_rcv;

{
	msg_xmt->msg_remote_port = msg_rcv->h.msg_remote_port;
	msg_xmt->msg_local_port = PORT_NULL;
	msg_xmt->msg_id = 0x12345678;
	msg_xmt->msg_size = sizeof(msg_header_t);
	msg_xmt->msg_type = MSG_TYPE_NORMAL;
	msg_xmt->msg_simple = TRUE;
}



/* This procedure is used by the child to get the communication port.
 * The child got the name as part of its inherited static variable space.
 * Port rights, however, are not inherited across forks. env_get_port,
 * a utility of the environment manager is called to return the port
 * associated with the given name.  
 */

port_t LookFor(name)
	env_name_t	name;

{
	port_t		result;
	kern_return_t	error;
	
	if ((error = env_get_port(environment_port, name, 
		&result)) != KERN_SUCCESS) {
			mach_error("CHILD: env_get_port returned ", 
				error);
			exit(1);
		}

	printf("CHILD: Successful env_get_port.\n");
	return(result);
}




/* This routine is used by the parent to create a port, and to associate the 
 * port name with the port via the environment manager.
 * port_allocate is used to allocate a port, and then env_set_port is called
 * passing the name of the port, and the newly allocated port.   */

port_t Register(name)
	env_name_t		name;

{
	port_t		result;
	kern_return_t	error;

	if ((error = port_allocate(task_self(), &result)) != KERN_SUCCESS) {
		mach_error("PARENT: port_allocate returned value of ", error);
		exit(1);
	}
	if ((error = env_set_port(environment_port, name, 
		result)) != KERN_SUCCESS) {
		mach_error("PARENT: env_set_port returned value of ", error);
		exit(1);
	}
	printf("PARENT: Successful env_set_port.\n");
	return(result);
}




/* This routine is called to demonstrate the passing of a simple message.
 * Please see program comment for order of events. */

void child_routine(my_port)
	port_t		my_port;

{
	msg_return_t	ret;
	int		i;
	struct simp_msg_struct	msg_xmt, msg_rcv;

	setup_simp_request(&msg_xmt, my_port);	
	if ((ret = msg_rpc(&msg_xmt.h, MSG_OPTION_NONE, sizeof(msg_xmt), 0, 
		0)) != RPC_SUCCESS) {
		mach_error("CHILD: msg_rpc returned value of ", ret);
		exit(1);
	}
	printf("CHILD: Successful msg_rpc.\n");
}




void parent_routine(my_port)
	port_t		my_port;

{
	msg_return_t	ret;
	int		i;
	int		x;
	msg_header_t	msg_xmt;
	struct simp_msg_struct msg_rcv;

	msg_rcv.h.msg_local_port = my_port;
	msg_rcv.h.msg_size = sizeof(msg_rcv);
	if ((ret = msg_receive(&msg_rcv.h, MSG_OPTION_NONE, 0)) !=
		RCV_SUCCESS) {
		mach_error("PARENT: msg_receive returned value of ", ret);
		exit(1);
	}
	printf("PARENT: Successful msg_receive.\n");
	printf("PARENT: Data..");
	for (i = 0; i < MAXDATA; i++)
		printf("%d ", msg_rcv.inline_data[i]);
	printf("\n");
	setup_simp_reply(&msg_xmt, &msg_rcv);
	if ((ret = msg_send(&msg_xmt, MSG_OPTION_NONE, 
		0)) != SEND_SUCCESS){
		mach_error("PARENT: msg_send returned value of ", ret);
		exit(1);
	}
	printf("PARENT: Successful msg_send.\n");
}




main (argc, argv)
	int		argc;
	char		**argv;

{
	kern_return_t	err;
	port_t		my_port;
	env_name_t	port_name;
	int		fret;

	if (argc > 1) {
		printf("no arguments to simp_ipc\n");
		exit(1);
	}
 	/* create a port name that both the child and parent will know */
	sprintf(port_name, "ipc_test_%d", getpid());

	/* create and register port for parent to receive on */

	if ((my_port = Register(port_name)) == PORT_NULL)
		exit(1);

	/* fork returns 0 if child, and the child's ID to the parent.  */
	fret = fork();
	if (fret == 0) { /* child process */
		if ((my_port = LookFor(port_name)) == PORT_NULL) 
			exit(1);
		child_routine(my_port);
		printf("CHILD: Finished successfully.\n");
	}
	else if (fret >0) { /* parent process */
		parent_routine(my_port);
		if ((err = env_del_port(environment_port, port_name))
			!= KERN_SUCCESS) {
			mach_error("PARENT: env_del_port returned ", err);
			exit(1);
		}
		if ((err = port_deallocate(task_self(), my_port)) 
			!= KERN_SUCCESS) {
			mach_error("PARENT: port_deallocate returned ", err);
			exit(1);
		}
		printf("PARENT: Finished successfully.\n");
	}
	else  printf("Error from fork.\n");
}    
