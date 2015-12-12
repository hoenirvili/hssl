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
// function cu customize the output
// for base key buffer and simple buffers
void 
output(const void *buff, const size_t len, bool key)
{
	const char *buffer;
	const unsigned char *key_buff;
	// if it's a simple buffer
	if(!key) {
		// note that hex dump buff is just 8 bits example ffffffff
		// we are seeing the ffffffff because char is signed on our system
		// In c vararg funct such as printf will promote all int smaller than
		// int to int. Sincer char is an integer(8-bit signed integer in our 
		// case.
		buffer = (char*)buff;
		printf("Length: %lu\n",len);
		printf("Content char: ");
		for(size_t i=0; i<len; i++) {
			fprintf(stdout, "%c", buffer[i]);
		}
		printf("\nContent ASCI: ");
		for(size_t i=0; i<len; i++){
			printf("%d ",(int) buffer[i]);
		}
		printf("\nContent HEX: ");
		for(size_t i=0; i<len; i++) {
			fprintf(stdout,"%x ",buffer[i]);
		}
	}
	// if it's a key
	else {
		printf("\n");
		fprintf(stdout, "\n"KRED"Found a match\n"RESET"");
		printf("\n");
		// note that hex dump key buff its 2 bits example ff
		key_buff = (unsigned char*)buff;
		printf("Length: %lu\n",len);
		printf("Content char: ");
		for(size_t i=0; i<len; i++) {
			fprintf(stdout, "%c", key_buff[i]);
		}
		printf("\nContent ASCI: ");
		for(size_t i=0; i<len; i++){
			printf("%d ",(int) key_buff[i]);
		}
		printf("\nContent HEX: ");
		for(size_t i=0; i<len; i++) {
			fprintf(stdout,"%x ",key_buff[i]);
		}
	}
}

// debug function if the buffer contains "\n" chars
void 
enter(const char *buff, const size_t len)
{
	for(size_t i=0; i<len; i++) {
		if(buff[i] == '\n')
			printf("\nENTER FOUND AT INDEX:  %lu",i);
	}
}
// dump all file content to stdout
void
print_file_content(const char *path)
{
	// cache and init values
	FILE *fp;
	char *buffer = NULL;

	// treat the file like a text base file
	fp = Fopen(path, "rb");

	Fseek(fp, 0L, SEEK_END);
	// get the size of the file
	long int file_size = Ftell(fp);

	Fseek(fp, 0L, SEEK_SET);
	// leave it file_size because char is one byte
	buffer = Malloc((size_t)file_size);


	size_t buff_len = Fread(buffer, sizeof(*buffer), (size_t)file_size ,fp);
	//end the buffer
	buffer[buff_len] = '\0';
	//print output
	output(buffer, buff_len, false);
	enter(buffer, buff_len);
	// close the file
	Fclose(fp);
	// memory
	free(buffer);
}
// dump all info to stdout
void
info(const char *plaintext, const char *algo_t, 
	 const unsigned char *cryptotext)
{
	if (plaintext != NULL)
		fprintf(stdout, KBLU "PLAINTEXT\n"RESET"%s\n",plaintext);
	if(algo_t != NULL)
		fprintf(stdout, KBLU"ALGO TYPE : "RESET"%s\n",algo_t);
	if(cryptotext != NULL){
		fprintf(stdout, KBLU"CRYPTOTEXT\n"RESET"");
		for(size_t i=0; i<32; i++) {
			fprintf(stdout,"%x ", cryptotext[i]);
		}
	}
}
// just for stopping the execution
// good function for debugging
void 
break_intr(const int intr, const int count)
{
	if(intr == count)
		exit(EXIT_SUCCESS);
}
