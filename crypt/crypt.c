#include<string.h>
#include <mcrypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <mhash.h>
#include <time.h>

#define algorithm "twofish"
#define hash_algo MHASH_SHA1
#define mode  "cfb"
#define keymode "mcrypt_sha1"
#define keysize 16
#define saltsize 20
#define ivsize  64

KEYGEN data;

char* crypt_malloc(size_t size);
void crypt_random(char *buf, size_t size);
void putin_meg(char *ciphertext, char *salt, char *IV);
void read_meg(char *ciphertext, char *salt, char *IV);

int encrypt(char *password, char *plaintext, char *ciphertext)
{

	MCRYPT td;
	int i;
	char *key;
	char block_buffer;
	char *IV;
	char *salt;
	
	td = mcrypt_module_open(algorithm, NULL, mode, NULL);
	if (td == MCRYPT_FAILED)
	{
		printf("failed to open module\n");		
		return 1;
	}

	salt = crypt_malloc(saltsize);
	crypt_random(salt, saltsize);
//	printf("salt:%s\n",salt);
        IV = crypt_malloc(ivsize);
	crypt_random(IV, ivsize);
//	printf("IV:%s\n",IV);

	putin_meg(ciphertext, salt, IV);
	
	key = crypt_malloc(keysize);
	data.hash_algorithm[0] = hash_algo;
	data.count = 0;
	data.salt = salt;
	data.salt_size = saltsize;
	mhash_keygen_ext(KEYGEN_MCRYPT, data, key, keysize, password, strlen(password));
	printf("key:%s\n",key);

	i = mcrypt_generic_init(td, key, keysize, IV);
        if (i<0) 
	{
        	mcrypt_perror(i);
        	return 1;
        }
//	printf("%d",strlen(plaintext));
// Here to encrypt in CFB performed in bytes 
        for(i=36; i<strlen(plaintext); i++)
	{
//		printf("%c",plaintext[i]);
		block_buffer = plaintext[i];
        	mcrypt_generic (td, &block_buffer, 1);
        	ciphertext[i] = block_buffer; 

//		printf("%c",ciphertext[i]);
	}

// Deinit the encryption thread, and unload the module 
         mcrypt_generic_end(td);

         return 0;

}

char *crypt_malloc(size_t size)
{
	char *x;
	
	if(size==0)
		return NULL;
	x = malloc(size);
	if(x!=NULL)
		return x;
	else
	{
		printf("Can't allocate memory!\n");
		exit(-1);
	}
}
	
void crypt_random(char *buf, size_t size)
{
	int i;
	
	srand(time(0));
	for(i=0;i<size;i++)
	{
		buf[i]=rand();
	}
}

void putin_meg(char *ciphertext, char *salt, char *IV)
{
	
	strcpy(ciphertext, salt);
	strcat(ciphertext, IV);	
}

void read_meg(char *ciphertext, char *salt, char *IV)
{
	int i;
	
	for (i=0; i< saltsize; i++)
	{
        	salt[i] = ciphertext[i];
        }
	
	for(i=saltsize; i<ivsize; i++)
	{
		IV[i] = ciphertext[i];
	}
	
}

int dencrypt(char *password, char *ciphertext, char *plaintext)
{

	MCRYPT td;
	int i;
	char *key;
	char block_buffer;
	char *IV;
	char *salt;	
	
	td = mcrypt_module_open(algorithm, NULL, mode, NULL);
	if (td==MCRYPT_FAILED)
	{
		return 1;
	}

	salt = crypt_malloc(saltsize);
        IV = crypt_malloc(ivsize);

	read_meg(ciphertext, salt, IV);

        i=mcrypt_generic_init( td, key, keysize, IV);
        if (i<0) 
	{
        	mcrypt_perror(i);
        	return 1;
        }
//	printf("%d",strlen(plaintext));
        for(i=saltsize + ivsize; i<=strlen(ciphertext); i++)
	{
//		printf("%c",plaintext[i]);
		block_buffer=ciphertext[i];
//Here begin to decrypt
       		mdecrypt_generic (td, &block_buffer, 1); 
        	plaintext[i]=block_buffer; 
//		printf("%c",ciphertext[i]);
	}

         mcrypt_generic_end(td);

         return 0;

       }

