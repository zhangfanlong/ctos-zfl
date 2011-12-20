//virtual_memory_interface.c
/*
*/

int main(int argc,char* argv[])
{
//5.1Memory Allocation
kern_return_t vm_allocate(vm_task_t(or mach_port_t) target_task, 
						  vm_address_t *address, 
						  vm_size_t size, 
						  boolean_t anywhere);
//5.2 Memory Deallocation
kern_return_t vm_deallocate(vm_task_t target_task,
							vm_address_t address,
							vm_size_t size);
//5.3 Data Transfer
kern_return_t vm_read(vm_task_t target_task,
					  vm_address_t address,
					  vm_size_t size,
					  vm_offset_t *data,
					  mach_msg_type_number_t *data_count);
					  
kern_return_t vm_write(vm_task_t target_task,
					   vm_address_t address,
					   vm_offset_t data,
					   mach_msg_type_number_t data_count);
					   
kern_return_t vm_copy(vm_task_t target_task,
					  vm_address_t source_address,
					  vm_size_t count,
					  vm_offset_t dest_address);

//5.4 Memory Attributes
kern_return_t vm_region(vm_task_t target_task,
						vm_address_t *address,
						vm_size_t *size,
						vm_prot_t *protection,
						vm_prot_t *max_protection,
						vm_inherit_t *inheritance,
						boolean_t *shared,
						memory_object_name t *object_name,
						vm_offset_t *offset);

kern_return_t vm_protect(vm_task_t target_task,
						 vm_address_t address,
						 vm_size_t size,
						 boolean_t set_maximum,
						 vm_prot_t new_protection);

kern_return_t vm_inherit(vm_task_t target_task,
						 vm_address_t address,
						 vm_size_t size,
						 vm_inherit_t new_inheritance);
						 
kern_return_t vm_inherit(vm_task_t target_task,
						 vm_address_t address,
						 vm_size_t size,
						 vm_inherit_t new_inheritance);
						
kern_return_t vm_machine_attribute(vm_task_t task,
								   vm_address_t address,
								   vm_size_t size,
								   vm_prot_t access,
								   vm_machine_attribute_t attribute,
								   vm_machine_attribute_val_t value);

//5.5 Mapping Memory Objects
kern_return_t vm_map(vm_task_t target_task,
					 vm_address_t *address,
					 vm_size_t size,
					 vm_address_t mask,
					 boolean_t anywhere,
					 memory_object_t memory_object,
					 vm_offset_t offset,
					 boolean_t copy,
					 vm_prot_t cur_protection,
					 vm_prot_t max_protection,
					 vm_inherit_t inheritance);

//5.6 Memory Statistics
kern_return_t vm_statistics(vm_task_t target_task,
							vm_statistics_data_t *vm_stats);
							

	return 0;
}