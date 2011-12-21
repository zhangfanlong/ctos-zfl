//vm_address_t_and_vm_offset_t.c

/*关于vm_address_t和vm_offset_t的一些测试
vm_address_t和vm_offset_t是同一个东西，是无符号整数，占4个字节。
定义了vm_address_t和vm_offset_t的数据结构与该类型的指针，
写入数据100并查看。
*/

/*从vm_address_t和vm_offset_t的声明上看，这两者是完全相同的东西，都是无符号的32位整数，占用4个字节。
但是所表示的意义是不一样的。
vm_address_t用于表示某个内存区域的某个字节，
而vm_offset_t表示内存对象的偏移或者其他的含义，要看上下文。
*/

# include <stdio.h>
# include <mach.h>

int main(int argc,char *argv[])
{
	vm_address_t address;
	vm_address_t *paddress=NULL;
	vm_offset_t offset;
	vm_offset_t *poffset=NULL;

	int address_size,offset_size;
	
	paddress=&address;
	address_size=sizeof(address);
	address=100;
	printf("the address size is %d\n",address_size);
	printf("the address is %d	%d\n",&address,address);
	printf("the paddress is %d	%d	%d\n",&paddress,paddress,*paddress);
	
	offset_size=sizeof(offset);
	offset=100;
	poffset=&offset;
	printf("the offst size is %d\n",offset_size);
	printf("the offset is %d	%d\n",&offset,offset);
	printf("the poffset s %d	%d	%d\n",&poffset,poffset,*poffset);

	printf("exiting\n");
	return 0;

}
