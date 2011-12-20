//GNU Mach External Memory Management

#include <mach.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

//6.1 Memory Object Server
/*boolean_t memory_object_server (msg header t *in_msg, msg header t *out_msg);
  boolean_t memory_object_default_server (msg header t *in_msg, msg header t *out_msg);
  boolean_t seqnos_memory_object_server (msg header t *in_msg, msg header t *out_msg);
  boolean_t seqnos_memory_object_default_server (msg header t *in_msg, msg header t *out_msg);
*/

//6.2 Memory Object Creation
/*memory_object_init()
Initializes a memory object
kern_return_t memory_object_init(memory_object_t memory_object,
								 memory_object_control_t memory_control,
								 memory_object_name_t memory_object_name,
								 vm_size_t memory_object_page_size);
*/
/*memory_object_ready()
Marks a memory object is ready to receive paging operations
kern_return_t memory_object_ready(memory_object_control_t memory_control,
								  boolean_t may_cache_object,
								  memory_object_copy_strategy_t copy_strategy);
*/


//6.3 Memory Object Termination
/*memory_object_terminate()
Relinquishes access to a memory object
kern_return_t memory_object_terminate(memory_object_t memory_object,
									  memory_object_control_t memory_control,
									  memory_object_name_t memory_object_name);									  
*/
/*memory_object_destroy()
Shuts down a memory object
kern_return_t memory_object_destroy(memory_object_control_t memory_control,
									kern_return_t reason);
*/

//6.4 Memory Objects and Data
/*memory_object_data_return��Writes data back to a memory object
д����,���ڴ���data������д�뵽object�е�offset��
kern_return_t memory_object_data_return(memory_object_t memory_object,
										memory_object_control_t memory_control,
										vm_offset_t offset,
										vm_offset_t data,
										vm_size_t data_count,
										boolean_t dirty,
										boolean_t kernel_copy);
*/
/*memory_object_data_request:Requests data from a memory object
ʹ���ݿ��Է��ʣ����뵽�ڴ��У�ʹ�ÿ��Է��ʡ�
kern_return_t memory_object_data_request(memory_object_t memory_object,
									     memory_object_control_t memory_control,
										 vm_offset_t offset,
										 vm_offset_t length,
										 vm_prot_t desired_access);
*/
/*memory_object_data_supply��Supplies data for a region of a memory object
�����װ�
kern_return_t memory_object_data_supply (memory_object_control_t memory_control, 
										 vm_offset_t offset,
										 vm_offset_t data,
										 vm_size_t data_count,
										 vm_prot_t lock_value,
										 boolean_t precious,
										 mach_port_t reply);
*/
/*
The function memory_object_supply_completed indicates that 
a previous memory_ object_data_supply has been completed.
kern_return_t memory_object_supply_completed(memory_object_t memory_object,
											 memory_object_control t memory_control,
											 vm_offset_t offset,
											 vm_size_t length,
											 kern_return_t result,
											 vm_offset_t error_offset);
*/
/*
The function memory_object_data_error indicates that the memory manager cannot 
return the data requested for the given region, specifying a reason for the error. 
This is typically used when a hardware error is encountered.
kern_return_t memory_object_data_error (memory_object_control_t memory_control,
										vm_offset_t offset,
										vm_size_t size,
										kern_return_t reason);
*/
/*
The function memory_object_data_unavailable indicates that 
the memory object does not have data for the given region and
that the kernel should provide the data for this range. 
kern_return_t memory_object_data_unavailable(memory_object_control_t memory_control,
											 vm_offset_t offset,
											 vm_size_t size,
											 kern_return_t reason);
*/
/*
kern_return_t memory_object_copy (memory_object_t old_memory_object,
								  memory_object_control_t old_memory_control,
								  vm_offset_t offset,
								  vm_size_t length,
								  memory_object_t new_memory_object);
*/
/*
��ʹ�õĽӿ�
memory_object_data_write();
memory_object_data_provided();
*/

//6.5Memory Object Locking
/*Restricts access to memory object data
kern_return_t memory_object_lock_request(memory_object_control_t memory_control,
										 vm_offset_t offset,
										 vm_size_t size,
										 memory_object_return_t should_clean,
										 boolean_t should_flush,
										 vm_prot_t lock_value,
										 mach_port_t reply_to);
*/

//Memory Object Attributes
/*
//The memory_object_get_attributes function retrieves the current attributes for the specified memory object.
kern_return_t memory_object_get_attributes(memory_object_control_t memory_control,
										   boolean_t *object_ready,
										   boolean_t *may_cache_object,
										   memory_object_copy_strategy_t *copy_strategy);
/*
kern_return_t memory_object_change_attributes(memory_object_control_t memory_control,
											  boolean_t may_cache_object,
											  memory_object_copy_strategy_t copy_strategy,
											  mach_port_t reply_to);
*/
/*
kern_return_t memory_object_change_completed(memory_object_t memory_object, 
											 boolean_t may_cache_object,
											 memory_object_copy_strategy_t copy_strategy);
*/
/*����ʽ�Ķ�����
kern_return_t memory_object_set_attributes 
*/


//6.7Default Memory Manager
/*����Ĭ��memory manager
vm_set_default_memory_manager
kern_return_t vm_set_default_memory_manager (host_t host,
											 mach_port_t *default_manager);
*/
/*�����ܱ�ʹ��.
�ں˴�����kernel-created memory object�������ڴ���ʱ���ڴ���󡣲����Ըı������ݲ��Ҳ����Ա�����������map��
kern_return_t memory_object_create(memory_object_t old_memory_object,
									 memory_object_t new_memory_object,
									 vm_size_t new_object_size,
									 memory_object_control_t new_control,
									 memory_object_name_t new_name,
									 vm_size_t new_page_size);
*/
/*��ʼ�������Ķ���
kern_return_t memory_object_data_initialize(memory_object_t memory_object,
											memory_object_control_t memory_control,
											vm_offset_t offset,//offset is the offset within a memory object to which this call refers.
											vm_offset_t data,
											vm_size_t data_count);
*/

	return 0;
}
