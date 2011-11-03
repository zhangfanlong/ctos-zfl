/* receive_integer.c, second needed function in our IPC example.

   Remember that is example code; for this to be real usable
   code you need some send_integer function and also a main
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
		    
	if( err == MACH_MSG_SUCCESS )
	  {
	    printf( "success: the message was received\n" );
	  }
	else
	  {
	    perror( "error: Some unexpected error ocurred\n" );
	    exit(err);
	  }
    
	*ip = message.inline_integer;
    
	return;
}
