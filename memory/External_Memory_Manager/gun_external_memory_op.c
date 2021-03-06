//GNU Mach External Memory Management
//gun_external_memory_op.c

/*
外部内存管理的所有接口。
可以使用内存对象和vm_map()完成内存共享，怎样实现还在探索中。
*/

#include <mach.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

//6.1 Memory Object Server
/*A memory manager is a server task that responds to 
specific messages from the kernel in order to 
handle memory management functions for the kernel.
*/
//为内核处理message。
boolean_t memory_object_server (msg header t *in_msg, msg header t *out_msg);
boolean_t memory_object_default_server (msg header t *in_msg, msg header t *out_msg);
boolean_t seqnos_memory_object_server (msg header t *in_msg, msg header t *out_msg);
boolean_t seqnos_memory_object_default_server (msg header t *in_msg, msg header t *out_msg);


//6.2 Memory Object Creation内存对象创建
/*
memory_object_init()；
memory_object_ready()；
*/
//memory_object_init():Initializes a memory object
kern_return_t memory_object_init(memory_object_t memory_object,
								 memory_object_control_t memory_control,
								 memory_object_name_t memory_object_name,
								 vm_size_t memory_object_page_size);

//memory_object_ready():Marks a memory object is ready to receive paging operations
kern_return_t memory_object_ready(memory_object_control_t memory_control,
								  boolean_t may_cache_object,
								  memory_object_copy_strategy_t copy_strategy);


//6.3 Memory Object Termination
/*
memory_object_terminate();
memory_object_destroy();
*/
//memory_object_terminate():Relinquishes access to a memory object
kern_return_t memory_object_terminate(memory_object_t memory_object,
									  memory_object_control_t memory_control,
									  memory_object_name_t memory_object_name);									  

//memory_object_destroy():Shuts down a memory object
kern_return_t memory_object_destroy(memory_object_control_t memory_control,
									kern_return_t reason);

//6.4 Memory Objects and Data
/*
memory_object_data_return();
memory_object_data_request();
memory_object_data_supply();
memory_object_supply_completed();
memory_object_data_error();
memory_object_data_unavailable();
memory_object_copy()
*/
//memory_object_data_return()：Writes data back to a memory object
//写数据,将内存中data的数据写入到object中的offset中
kern_return_t memory_object_data_return(memory_object_t memory_object,
										memory_object_control_t memory_control,
										vm_offset_t offset,
										vm_offset_t data,
										vm_size_t data_count,
										boolean_t dirty,
										boolean_t kernel_copy);

//memory_object_data_request():Requests data from a memory object
//访问数据。
kern_return_t memory_object_data_request(memory_object_t memory_object,
									     memory_object_control_t memory_control,
										 vm_offset_t offset,
										 vm_offset_t length,
										 vm_prot_t desired_access);

//memory_object_data_supply()：Supplies data for a region of a memory object
/*
同memory_object_data_request（）相似，具体？？
提供给内核数据（指定内存对象）：
*/
kern_return_t memory_object_data_supply (memory_object_control_t memory_control, 
										 vm_offset_t offset,
										 vm_offset_t data,
										 vm_size_t data_count,
										 vm_prot_t lock_value,
										 boolean_t precious,
										 mach_port_t reply);


//memory_object_supply_completed():
/*The function memory_object_supply_completed indicates that 
a previous memory_ object_data_supply has been completed.
*/
//supply 是否完成。
kern_return_t memory_object_supply_completed(memory_object_t memory_object,
											 memory_object_control t memory_control,
											 vm_offset_t offset,
											 vm_size_t length,
											 kern_return_t result,
											 vm_offset_t error_offset);

//memory_object_data_error()
/*
The function memory_object_data_error indicates that the memory manager cannot 
return the data requested for the given region, specifying a reason for the error. 
This is typically used when a hardware error is encountered.
*/
//数据错误
kern_return_t memory_object_data_error (memory_object_control_t memory_control,
										vm_offset_t offset,
										vm_size_t size,
										kern_return_t reason);

//memory_object_data_unavailable()
/*
The function memory_object_data_unavailable indicates that 
the memory object does not have data for the given region and
that the kernel should provide the data for this range. 
*/
//数据不可用
kern_return_t memory_object_data_unavailable(memory_object_control_t memory_control,
											 vm_offset_t offset,
											 vm_size_t size,
											 kern_return_t reason);

//memory_object_copy()
//copy已有的内存对象
kern_return_t memory_object_copy (memory_object_t old_memory_object,
								  memory_object_control_t old_memory_control,
								  vm_offset_t offset,
								  vm_size_t length,
								  memory_object_t new_memory_object);

/*
已经不在使用的接口，老的接口
*/
memory_object_data_write();
memory_object_data_provided();


//6.5Memory Object Locking
/*
memory_object_lock_request();
memory_object_lock_completed();
memory_object_data_unlock();
*/
//Restricts access to memory object data
kern_return_t memory_object_lock_request(memory_object_control_t memory_control,
										 vm_offset_t offset,
										 vm_size_t size,
										 memory_object_return_t should_clean,
										 boolean_t should_flush,
										 vm_prot_t lock_value,
										 mach_port_t reply_to);
kern_return_t memory_object_lock_completed(memory_object_t memory_object,
										   memory_object_control_t memory_control,
										   vm_offset_t offset,
										   vm_size_t length);
kern_return_t memory_object_data_unlock(memory_object_t memory_object,
									    memory_object_control_t memory_control,
										vm_offset_t offset,
										vm_size_t length,
										vm_prot_t desired_access);

//6.6 Memory Object Attributes
/*
memory_object_get_attributes();
memory_object_change_attributes();
memory_object_change_completed();
*/
//The memory_object_get_attributes function retrieves the current attributes for the specified memory object.
kern_return_t memory_object_get_attributes(memory_object_control_t memory_control,
										   boolean_t *object_ready,
										   boolean_t *may_cache_object,
										   memory_object_copy_strategy_t *copy_strategy);

kern_return_t memory_object_change_attributes(memory_object_control_t memory_control,
											  boolean_t may_cache_object,
											  memory_object_copy_strategy_t copy_strategy,
											  mach_port_t reply_to);

//
kern_return_t memory_object_change_completed(memory_object_t memory_object, 
											 boolean_t may_cache_object,
											 memory_object_copy_strategy_t copy_strategy);

/*旧形式的东西，
kern_return_t memory_object_set_attributes 
*/


//6.7Default Memory Manager
/*
vm_set_default_memory_manager();
memory_object_create();
memory_object_data_initialize();
*/
//设置默认memory manager:vm_set_default_memory_manager
kern_return_t vm_set_default_memory_manager (host_t host,
											 mach_port_t *default_manager);

/*将不能被使用.
内核创建（kernel-created memory object）的是内存临时的内存对象。不可以改变以内容并且不可以被其他的任务map。
*/
kern_return_t memory_object_create(memory_object_t old_memory_object,
									 memory_object_t new_memory_object,
									 vm_size_t new_object_size,
									 memory_object_control_t new_control,
									 memory_object_name_t new_name,
									 vm_size_t new_page_size);

//初始化创建的对象
kern_return_t memory_object_data_initialize(memory_object_t memory_object,
											memory_object_control_t memory_control,
											vm_offset_t offset,//offset is the offset within a memory object to which this call refers.
											vm_offset_t data,
											vm_size_t data_count);

											
											
											
	return 0;
}
