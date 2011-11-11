#include <string.h>
#include <stdio.h>
#include <mcrypt.h>

int main()
{
	MCRYPT td;
	td = mcrypt_module_open(MCRYPT_DES, NULL, MCRYPT_CBC, NULL);
	if(td == MCRYPT_FAILED)
		err(1, "mcrypt failed");

	int keysize = mcrypt_enc_get_key_size(td);
	char *key = "uLeeCo6riemoJoyaip5ohvaeniesoo2h";

	int blocksize = mcrypt_enc_get_block_size(td);
	char *block;

	int ivsize = mcrypt_enc_get_iv_size(td);	
	char *IV;
	IV = malloc(ivsize);	
	int i;
	for (i=0; i< ivsize; i++) {
		IV[i]=rand();
  	}
	
	mcrypt_generic_init(td, key, keysize, IV);

	char msg[256];
	bzero(msg, 256);
	printf("Enter message to encrypt: ");
	scanf("%s", msg);
	int msglen = strlen(msg);
	msg[msglen] = '0';
	msglen += blocksize - (msglen%blocksize);
	msg[msglen] = '0';
	int k = msglen/blocksize;
	
	mcrypt_generic(td, &msg[(k-1)*blocksize], blocksize);
	printf("Encrypted message: %s\n", msg);

	mcrypt_generic_deinit(td);
	mcrypt_module_close(td);
/*******************************************/
	k = msglen/blocksize;
	td = mcrypt_module_open(MCRYPT_DES, NULL, MCRYPT_CBC, NULL);
	mcrypt_generic_init(td, key, keysize, IV);

	mdecrypt_generic(td, &msg[(k-1)*blocksize], blocksize);
	printf("Decrypted message: %s\n", msg);

	mcrypt_generic_deinit(td);
	mcrypt_module_close(td);
	return 0;		
}
