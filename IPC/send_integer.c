/* send_integer.c, an example of constructing a function that makes
   easy IPC operations, with a clear interface.

   Remember that is example code; for this to be real usable
   code you need some receive_integer function and also a main
   function.

   Written by Manuel Pavón Valderrama <mpavon@ugr.es, cp46tan@hotpop.com>,
   2002.

   (c) Copyright by Manuel Pavón Valderrama 
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
	if( err == MACH_MSG_SUCCESS )
	  {
	    printf( "success: the message was queued\n" );
	  }
	else
	  {
	    perror( "error: some unexpected error ocurred!\n");
	    exit(err);
	  }

	return;
}
