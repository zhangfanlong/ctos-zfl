/* Hello world ?la mach ipc.
   Copyright (C) 2002 Neal H. Walfield  <neal@cs.uml.edu>

   This is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program has been distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111,
   USA. */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <cthreads.h>
#include <mach.h>

struct message
{
  mach_msg_header_t header;
  mach_msg_type_t type;
  char data[256];
};

any_t server (any_t arg)
{
  mach_port_t port = *(mach_port_t *) arg;
  int err;
  struct message message;

  message.header.msgh_local_port = port;
  message.header.msgh_size = sizeof (message);

  while (1)
    {
      /* Receive a message.  */
      err = mach_msg (&message.header,		/* The header */
		      MACH_RCV_MSG,		/* Flags */
		      0, sizeof (message),	/* Send/Max receive size */
		      port,			/* Receive port */
		      MACH_MSG_TIMEOUT_NONE,	/* No timeout */
		      MACH_PORT_NULL);		/* No notification */
      if (err)
	error (1, err, "mach_msg");
         
      /* Verify the type tag */
      assert (message.type.msgt_name == MACH_MSG_TYPE_STRING);

      /* Copy the contents so that we can create a reply string.  */
      {
        char *temp = strdup (message.data);
        sprintf (message.data, "Hello %s", temp);
        free (temp);
      }

      /* Fix the header.  */
      message.header.msgh_local_port = MACH_PORT_NULL;

      /* Fix the type header.  */
      message.type.msgt_size += strlen ("Hello ") * 8;

      /* Send the reply.  */
      err = mach_msg (&message.header,		/* The message header */
		      MACH_SEND_MSG,		/* Flags */
		      sizeof (message), 0,	/* Send/Max receive size */
		      MACH_PORT_NULL,		/* Receive port */
		      MACH_MSG_TIMEOUT_NONE,	/* No timeout */
		      MACH_PORT_NULL);		/* No notification */
      if (err)
        error (2, err, "mach_msg");
    }
    
  return 0;
}   

int main (int argc, char *argv[])
{
  mach_port_t port;
  mach_port_t receive;
  int err;

  /* Allocate a port.  */
  err = mach_port_allocate (mach_task_self (),
     		      	    MACH_PORT_RIGHT_RECEIVE, &port);
  if (err)
    error (1, err, "mach_port_allocate");

  err = mach_port_allocate (mach_task_self (),
     		      	    MACH_PORT_RIGHT_RECEIVE, &receive);
  if (err)
    error (1, err, "mach_port_allocate");

  /* Create a new thread to wait for the message */
  cthread_detach (cthread_fork (server, (void *) &port));

  /* Send a message down the port */
  while (1)
    {
      struct message message;

      printf ("Enter your name: ");
      fgets (message.data, sizeof (message.data) - 1, stdin);

      if (feof (stdin))
	break;

      message.header.msgh_bits
	= MACH_MSGH_BITS (MACH_MSG_TYPE_MAKE_SEND,
			  MACH_MSG_TYPE_MAKE_SEND_ONCE);
      message.header.msgh_remote_port = port;		/* Request port */
      message.header.msgh_local_port = receive;		/* Reply port */
      message.header.msgh_id = 0;			/* Message id */
      message.header.msgh_size = sizeof (message);	/* Message size */

      message.type.msgt_name = MACH_MSG_TYPE_STRING;	/* Parameter type */
      message.type.msgt_size = 8 * (strlen (message.data) + 1); /* # Bits */
      message.type.msgt_number = 1;			/* Number of elements */
      message.type.msgt_inline = TRUE;			/* Inlined */
      message.type.msgt_longform = FALSE;		/* Shortform */
      message.type.msgt_deallocate = FALSE;		/* Do not deallocate */
      message.type.msgt_unused = 0;			/* = 0 */

      /* Send the message on its way and wait for a reply.  */
      err = mach_msg (&message.header,			/* The header */
	    	      MACH_SEND_MSG | MACH_RCV_MSG,	/* Flags */
		      sizeof (message),			/* Send size */
		      sizeof (message),			/* Max receive Size */
		      receive,				/* Receive port */
		      MACH_MSG_TIMEOUT_NONE,		/* No timeout */
		      MACH_PORT_NULL);			/* No notification */
      if (err)
        error (3, err, "mach_msg");

      /* Verify the type tag */
      assert (message.type.msgt_name == MACH_MSG_TYPE_STRING);

      printf ("Server said: %s", message.data);
    }

  return 0;
}
