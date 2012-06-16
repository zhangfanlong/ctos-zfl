
#ifndef _data_user_
#define _data_user_

/* Module data */

#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/message.h>

#include <mach/std_types.h>
#include <mach/mach_types.h>
#include <device/device_types.h>
#include <device/net_status.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <hurd/hurd_types.h>

/* Routine data_set_value */
#ifdef  mig_external
mig_external
#else
extern
#endif
kern_return_t S_data_set_value
#if defined(LINTLIBRARY)
    (data_port, value)
    mach_port_t data_port;
    int value;
{ return S_data_set_value(data_port, value); }
#else
(
    mach_port_t data_port,
    int value
);
#endif

/* Routine data_get_value */
#ifdef  mig_external
mig_external
#else
extern
#endif
kern_return_t S_data_get_value
#if defined(LINTLIBRARY)
    (data_port, value)
    mach_port_t data_port;
    int *value;
{ return S_data_get_value(data_port, value); }
#else
(
    mach_port_t data_port,
    int *value
);
#endif

#endif  /* not defined(_data_user_) */
