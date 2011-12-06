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
/*memory_object_data_return：Writes data back to a memory object
写数据咯
kern_return_t memory_object_data_return(memory_object_t memory_object, 
										memory_object_control_t memory_control,
										vm_offset_t offset, 
										vm_offset_t data, 
										vm_size_t data_count, 
										boolean_t dirty, 
										boolean_t kernel_copy);
*/
/*
kern_return_t memory_object_data_request(memory_object_t memory_object,
									     memory_object_control_t memory_control,
										 vm_offset_t offset,
										 vm_offset_t length,
										 vm_prot_t desired_access);
*/
/*
kern_return_t memory_object_data_supply (memory_object_control_t memory_control, 
										 vm_offset_t offset, 
										 vm_offset_t data, 
										 vm_size_t data_count, 
										 vm_prot_t lock_value, 
										 boolean_t precious, 
										 mach_port_t reply);
*/
/*
kern_return_t memory_object_supply_completed(memory_object_t memory_object, 
											 memory_object_control t memory_control, 
											 vm_offset_t offset, 
											 vm_size_t length, 
											 kern_return_t result, 
											 vm_offset_t error_offset);
*/
/*
kern_return_t memory_object_data_error (memory_object_control_t memory_control, 
										vm_offset_t offset, 
										vm_size_t size, 
										kern_return_t reason);
*/
/*
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
不使用的接口
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
											  mach_port_t reply_to)
*/
/*
kern_return_t memory_object_change_completed(memory_object_t memory_object, 
											 boolean_t may_cache_object, 
											 memory_object_copy_strategy_t copy_strategy);
*/
/*旧形式的东西，
kern_return_t memory_object_set_attributes 
*/


//Default Memory Manager
/*设置默认memory manager
vm_set_default_memory_manager
kern_return_t vm_set_default_memory_manager (host_t host,
											 mach_port_t *default_manager);
*/
/*将不能被使用.
内核创建（kernel-created memory object）的是内存临时的内存对象。不可以改变以内容并且不可以被其他的任务map。
kern_return_t memory_object_create(memory_object_t old_memory_object,
									 memory_object_t new_memory_object,
									 vm_size_t new_object_size, 
									 memory_object_control_t new_control, 
									 memory_object_name_t new_name, 
									 vm_size_t new_page_size);
*/
/*初始化创建的对象
kern_return_t memory_object_data_initialize(memory_object_t memory_object, 
											memory_object_control_t memory_control,
											vm_offset_t offset, 
											vm_offset_t data, 
											vm_size_t data_count);
*/

	return 0;
}
