//mach_self.c
/*获得一些基本信息：
使用mach_task_self()获得task.
使用mach_host_self()获得host.
*/
#include <stdio.h>
#include <mach.h>

/*测试结果:
task=//未测试；
host=23;
*/
int main()
{
	host_t host;
	task_t task;
	
	kern_return_t kr;
	
	task=mach_task_self();
	printf("task is %d\n",task);
	host=mach_host_self();
	printf("host is %d\n",host);
	
	return 0;
}

