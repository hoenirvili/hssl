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

void 
alloc_globals(const char *ppath, const char* algpath, const char* crypto_path) {
	//ALLOC MEMORY BLOCKS
	plain_text = load_from_file(ppath);
	algorithm_type = load_from_file(algpath);
	crypto_text = load_from_file_hex(crypto_path);
}

void
free_globals(void)
{
	//free up the memory
	free(plain_text);
	free(algorithm_type);
	free(crypto_text);
}

void 
mechanism(const char *alg_path, const char* crypto_path, const EVP_CIPHER *algo_type)
{
	///main globals
	FILE *fp;
	// delcare our buffer of 2KBs
	char buffer[2*CHUNK];

	int intr = 0;
	unsigned char *encrypted_text= NULL;
	unsigned char *key = NULL;


	size_t n,i,j;

	alloc_globals(PLAINTEXT_PATH, alg_path, crypto_path);
	//Display statistics at the program loads
	info(plain_text, algorithm_type, crypto_text);

	// open the main file to load all result
	fp = Fopen("test_files/word_dict.txt", "rb");
	// load line per line per line into buffer of chunks
	while(Fgets(buffer, 2*CHUNK, fp) != NULL) {
		//count the number of lines
		intr++;
		// terminate the buffer
		buffer[strlen(buffer) - 1] = '\0';
		// if the word from  dictionary is lower or equal 
		// bytes chars process it
		if( (n = strlen(buffer)) <= 0x10) {
			// alloc the key
			key = Malloc(0x10 * (sizeof(unsigned char)+1));
			// save the begging of the key
			unsigned char *savePtr = key;
			// vor every char from the word of the dict
			for(i=0; i<n; i++) {
				// asigned the char from the dict to the key
				*key = (unsigned char)buffer[i];
				// increment the key
				key ++;
			}
			//
			// if we still have space in the key, fill all with space chars
			// or we could just at the beginning memset it to 0x20 all the 16 byts of the key
			// but anyway let's make it consistant
			for( j = i; j<=0x10; j++) {
				*key = 0x20;
				key++;
			}
			key = savePtr;
			// null terminate 
			key[0x11] = 0;
			encrypted_text = encrypt(key, algo_type);
			
			if(is_equal(encrypted_text, crypto_text)) {
				output(key, 16, true);
				free(key);
				break;
			}
			
			free(key);
		}//free
	}//while
	free_globals();
	fclose(fp);
}
