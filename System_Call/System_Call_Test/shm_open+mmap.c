//shm_open+mmapµÄÊ¾Àý³ÌÐò
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int fd = shm_open("test", O_RDWR|O_CREAT, S_IRWXU);
	if (fd < 0) {
		perror("shm_open() failed.");
		exit(1);
	}

	ftruncate(fd, 1024);//Bus error occuring without this line.

	char *buf;
	buf = mmap(0, 1024, PROT_READ|PROT_WRITE, 
				MAP_SHARED|MAP_32BIT, fd, 0);
	if (buf) 
		sprintf(buf, "good");
	else
		perror("mmap() failed.");
	return 0;
}


