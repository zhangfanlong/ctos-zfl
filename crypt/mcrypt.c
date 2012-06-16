#include <string.h>
#include <mhash.h>
#include <mcrypt.h>
#include <stdio.h>
#include <stdlib.h>


int encrypt(char *password, char *plaintext, char *ciphertext)
{
	MCRYPT td;
	int i;
	char *key;
	char *block_buffer;
	char *IV;
	
	key=calloc(1,16);
	mhash_keygen();
	
	td=mcrypt_module_open("twofish",NULL,"cfb",NULL);
	if(td==MCRYPT_FAILED)
	{
		return -1;
	}

	IV=malloc(mcrypt_enc_get_iv_size(td));
	srand(time(0));
	for(i=0;i<mcrypt_enc_get_iv_size(td);i++)
	{
		IV[i]=rand();
	}

	i=mcrypt_generic_init(td,key,keysize,IV)
	if(i<0)
	{
		mcrypt_perror(i);
		return 1;
	}

	while(fread(&block_buffer,1,1,plaintext)==1)
	{
		mcrypt_generic(td,&block_buffer,1);
		fwrite(&block_buffer,1,1,ciphertext);
	}

	mcrypt_generic_end(td);

	return 0;

}
