/*
memory_object_mmap.c
ʹ��mmap��memory objectʵ�ֵ��ڴ湲��
*/

/*ʹ��vm_map()�����µ��ڴ���󣬲��������һϵ�еĲ������ԡ�
��Ҫʹ��memory object�ڴ������صĽӿڡ�
*/

#include <mach.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	//�����������ʼ��
	kern_return_t kr;
	vm_task_t target_task=mach_task_self();
	vm_address_t *address=NULL;
	vm_size_t size=vm_page_size;
	vm_address_t mask;//mask�������ã�
	boolean_t anywhere=TURE;
	memory_object_t memory_object=MEMORY_OBJECT_NULL;
	vm_offset_t offset=0;
	boolean_t copy=FALSE;
	vm_prot_t cur_protection=(VM_PORT_READ|VM_PORT_WRITE);//��ǰ�������ԣ���д
	vm_prot_t max_protection=(VM_PORT_READ|VM_PORT_WRITE);//��󱣻����ԣ���д
	vm_inherit_t inheritance=VM_INHERIT_SHARE;//�������ù���

	kr=0;

	//����һ���µ��ڴ����ʹ��vm_map()��
	kr=vm_map(target_task,*address,size,mask,anywhere,
				memory_object,offset,copy,cur_protection,
				max_protection, inheritance);
	if(kr)
		{
			mach_error("the value of error is",kr);
			printf("vm_map() is exiting:%d\n",kr);
			return kr;
		}
	printf("vm_map is ok\n");
	

}