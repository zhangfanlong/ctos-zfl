#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#define TEST "testnomal"
int main()
{

	int fd=shm_open(TEST,O_RDWR|O_CREAT,S_IRWXU);
	if(fd<0)
	{
	perror("shm_open failed!\n");	
	exit(1);
	}

	ftruncate(fd,1024);
	char *buff;
	buff=mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(buff)
	{
		sprintf(buff,"good");
	}
	else
		perror("mmap()failed.");
        close(fd);
	shm_unlink(TEST);
	return 0;
}
