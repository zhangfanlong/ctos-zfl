
#include <stdio.h>
#include <hurd.h>
#include <hurd/hurd_types.h>
#include "data.h"

#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif

int
main(int argc, char *argv[])
{
  int value=0;
  mach_port_t data_server_port;

  data_server_port = file_name_lookup ("/tmp/trans", 0, 0);
  printf ("data_server_port [%u]\n", data_server_port);
  S_data_set_value (data_server_port, 99);
  S_data_get_value (data_server_port, &value);
  printf ("data->get_value: [%d]\n", value);

  return 0;
}
