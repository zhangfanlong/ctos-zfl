/* bootstrap_ipc_rename.c, a Mach IPC example :

	In this example, a Mach Task creates a port  ( or, if you prefer, 
   creates a port right; therefore a port is created by the Mach kernel ), 
   and send a message to itself ( this is why this example is 
   called bootstrap_ipc ). Between the send and receive operations
   the port name is renamed; some people may think too that 
   the code is cleaner, but that's only an opinion.

   Written by Manuel Pav�n Valderrama <mpavon@ugr.es, cp46tan@hotpop.com>,
   2002.

   (c) Copyright by Manuel Pav�n Valderrama 
   <mpavon@ugr.es, cp46tan@hotpop.com>, 2002.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330,
   Boston, MA  02111-1307  USA
 */
 
#define _GNU_SOURCE
 
#include <mach.h>

#include <stdio.h>
#include <error.h>

struct integer_message
{
	mach_msg_header_t head;
	mach_msg_type_t type;
    
	int inline_integer;
};

/* send_integer is a function that sends a given integer to some mach port;
   it also hides the complexity of using the mach_msg primitive to the user.

   send_integer takes to arguments : the port where you want to send 
   the message with an integer inside, and the integer that is inside the
   mentioned message. 
*/
void 
send_integer( mach_port_t destination, int i )
{
	kern_return_t err;
	struct integer_message message;

	/* (i) Form the message : */

	/* (i.a) Fill the header fields : */
	message.head.msgh_bits = 
		MACH_MSGH_BITS_REMOTE(MACH_MSG_TYPE_MAKE_SEND);
	message.head.msgh_size = sizeof( struct integer_message );
	message.head.msgh_local_port = MACH_PORT_NULL;
	message.head.msgh_remote_port = destination;
    
	/* (i.b) Explain the message type ( an integer ) */
	message.type.msgt_name = MACH_MSG_TYPE_INTEGER_32;
	message.type.msgt_size = 32;
	message.type.msgt_number = 1;
	message.type.msgt_inline = TRUE;
	message.type.msgt_longform = FALSE;
	message.type.msgt_deallocate = FALSE;
	/* message.type.msgt_unused = 0; */ /* not needed, I think */
    
	/* (i.c) Fill the message with the given integer : */
	message.inline_integer = i;
    
	/* (ii) Send the message : */
	err = mach_msg( &(message.head), MACH_SEND_MSG, 
			message.head.msgh_size, 0, MACH_PORT_NULL, 
			MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL );
		    
	/* (iii) Analysis of the error code; 
	if succes, print and acknowledge message and return */
	if( err == MACH_MSG_SUCCESS ){
		printf( "success: the message was queued\n" );
	}
	else{
		perror( "error: some unexpected error ocurred!\n");
		exit(1);
	}

	return;
}

/* receive_integer is a function that receives an integer from some 
   mach port; it also hides the complexity of using the mach_msg 
   primitive to the user.

   receive_integer takes two arguments; the port where the message is going
   to come from with an integer inside, and a pointer to an integer in where
   the integer contained in the mentioned message will be stored.
*/
void 
receive_integer( mach_port_t source, int *ip )
{
	kern_return_t err;
    
	struct integer_message message;
    
	/* (i) Fill the little thing we know about the message : */
	/* message.head.msgh_size = sizeof(struct integer_message ); */
    
	/* (ii) Receive the message : */
	err = mach_msg( &(message.head), MACH_RCV_MSG, 0, 
			message.head.msgh_size, source,
			MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL );
		    
	if( err == MACH_MSG_SUCCESS ){
		printf( "success: the message was received\n" );
	}
	else{
		perror( "error: Some unexpected error ocurred\n" );
		exit(1);
	}
    
	*ip = message.inline_integer;
    
	return;
}

/* main function of the program; it does the following :

   (i) allocate a port for receiving a message
   (ii) send a message containing an integer; 
   it uses the send_integer function
   (iii) receive the message and display it;
   it uses the receive_integer function
   (iv) deallocate the port
*/
int 
main( void )
{	    
	int s, r;	/* s -> int sent, r -> int received */ 
	mach_port_t destination, source;    

	kern_return_t err;
    
	/* Allocate a port to receive the bootstrap message : */
	err = mach_port_allocate( mach_task_self(), MACH_PORT_RIGHT_RECEIVE,
		&destination );

	if( err != KERN_SUCCESS ){
		perror( "Error : could not allocate any port\n" );
		exit(1);
	}
    
	/* Form and send the message : */
	s = 7; /* -> fill it with your favorite number */
	send_integer( destination, s );

	/* Make an alias for the source name : */    
	err = mach_port_rename( mach_task_self(), 
		destination, source );

	if( err != KERN_SUCCESS ){
		perror( "error : could not rename any port\n" );
		exit(err);
	}

	/* Receive the message and display it : */
	receive_integer( source, &r );

	printf("The received integer is : %d\n", r );
    
	mach_port_deallocate( mach_task_self(), destination );
    
	return(r);
} 
