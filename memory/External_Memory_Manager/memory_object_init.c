/*
��������ʹ��memory_object_init�����Լ�memory_object_destroy������
*/

#include<stdio.h>
#include<mach.h>

int main()
{

/*ʹ��memory_object_init�����Լ�memory_object_destroy����
  ʧ�ܡ�
  ���ش����ǣ�(ipc/send) invalid destination port.
	      krֵ��kr=268435459
*/
    memory_object_t memory_object;
	memory_object_control_t memory_control;
	memory_object_name_t memory_object_name;
	
	kern_return_t kr;
	kern_return_t reason;

	kr=memory_object_init(memory_object,memory_control,
						  memory_object_name, vm_page_size);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("memory_object_init() is exiting:%d\n",kr);
			//return kr;
		}
	printf("memory_object_init is ok\n");

	kr=memory_object_destroy(memory_control,reason);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("memory_object_destroy() is exiting.kr=%d\n",kr);
			//return kr;
		}
	//printf("every thing is ok,and main is exiting\n");

	
	return 0;
}