//vm_address_t_and_vm_offset_t.c

/*����vm_address_t��vm_offset_t��һЩ����
vm_address_t��vm_offset_t��ͬһ�����������޷���������ռ4���ֽڡ�
������vm_address_t��vm_offset_t�����ݽṹ������͵�ָ�룬
д������100���鿴��
*/

/*��vm_address_t��vm_offset_t�������Ͽ�������������ȫ��ͬ�Ķ����������޷��ŵ�32λ������ռ��4���ֽڡ�
��������ʾ�������ǲ�һ���ġ�
vm_address_t���ڱ�ʾĳ���ڴ������ĳ���ֽڣ�
��vm_offset_t��ʾ�ڴ�����ƫ�ƻ��������ĺ��壬Ҫ�������ġ�
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
