//mach_self.c
/*���һЩ������Ϣ��
ʹ��mach_task_self()���task.
ʹ��mach_host_self()���host.
*/
#include <stdio.h>
#include <mach.h>

/*���Խ��:
task=//δ���ԣ�
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

