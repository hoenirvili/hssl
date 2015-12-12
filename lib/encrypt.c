//	Copyright 12-11-2015 Hoenir
//
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.


#include "hssl.h"
//static FILE *out;
static int outlen, tmplen;
static unsigned char outbuf[2*CHUNK];

unsigned char* 
encrypt (unsigned char *key, const EVP_CIPHER *algo_type)
{
	//EVP
	EVP_CIPHER_CTX ctx;
	// initializes cipher context ctx
	EVP_CIPHER_CTX_init(&ctx);
	// init our context
	EVP_EncryptInit(&ctx, algo_type, key, NULL);
	// custom openssl asert function for debbuing reasons
	OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);

	if(!EVP_EncryptUpdate(&ctx, outbuf, &outlen, (unsigned char*)plain_text, (int)strlen(plain_text)))
	{
		fprintf(stderr, "Can't set update ctx struct");
		EVP_CIPHER_CTX_cleanup(&ctx);
		exit(EXIT_FAILURE);
	}

	if(!EVP_EncryptFinal(&ctx, outbuf+outlen, &tmplen))
	{
		fprintf(stderr, "Can't encrypt plaintext");
		EVP_CIPHER_CTX_cleanup(&ctx);
		exit(EXIT_FAILURE);
	}
	
	// free memmory
	EVP_CIPHER_CTX_cleanup(&ctx);
	
	// return our new encrypted buffer
	return outbuf;


}
// test if crypto text from file is equal to the new crypto
// text generated with the algo 
bool 
is_equal(unsigned char *a, unsigned char *b)
{
	// compare each 32 bytes
	for(size_t i =0; i<32; i++) {
		if(a[i] != b[i]) {
			return false;
		}
	}
	return true;
}


