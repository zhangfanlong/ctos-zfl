#include <stdlib.h>
#include <stdio.h>

//extern int dencrypt(char *password, char *ciphertext, char *plaintext);
//extern int encrypt(char *password, char *plaintext, char *ciphertext);
int main()
{
	char password[20]={"user password"};
	char plaintext[100]={"www.cms.hit.edu.cn"};
	char ciphertext[100]={""};

	encrypt(password,plaintext,ciphertext);
	printf("%s\n",ciphertext);
	dencrypt(password,ciphertext,plaintext);
	printf("%s\n",plaintext);

	return 0;
}
