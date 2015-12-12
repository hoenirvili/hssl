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
/**
 * It's very important to know that 
 * this call allocs bytes for buffer
 * and we need to free the mem when we finish
 * our process
 */
char *
load_from_file(const char* path)
{

	//cache and init values
	FILE *fp;
	char *buffer = NULL;
	// open file
	fp = Fopen(path, "rb");
	// set cursor on the end of the file
	Fseek(fp, 0L, SEEK_END);
	// get how many bytes to alloc for the buffer
	long int  file_size = Ftell(fp);
	// set cursor on the first line back
	Fseek(fp, 0L, SEEK_SET);
	// alloc the space in the buffer
	buffer = Malloc((size_t)(file_size+1));
	// read from the file 
	size_t buff_len = Fread(buffer, sizeof(*buffer), (size_t)file_size, fp);
	// end the buffer
	buffer[buff_len] = '\0';
	// close the file
	Fclose(fp);
	
	return buffer;
}
// incapsulate prive func
static size_t ReadHexFile(FILE *inf, unsigned char *dest) {
	size_t count=0;
	int n;
	// just compute the size of buffer
	if (dest == NULL) {
		unsigned char OneByte;
		while ((n = fscanf(inf, "%hhx", &OneByte)) == 1 ) {
			count++;
		}
	}
	else { // fill the dest buffer
	    while ((n = fscanf(inf, "%hhx", dest)) == 1 ) {
			dest++;
		}
	}
	// we've reached end of line
	if (n != EOF) {
		prog_error("End of line !",true, errno);
	}
	// return count
	// note that if dest isn't set just return 0
	return count;
}
// If we have a special binary file with spaces for 
// every byte just load all content in our hex buffer
// note that we alloc and we need to free the mem
unsigned char *load_from_file_hex(const char* path)
{
	FILE *inf = fopen(path, "rb");
	// calculate the size for alloc
	size_t n = ReadHexFile(inf, NULL);
	// get the cursor of file back up
    rewind(inf);
	// aloc some mem to fill all content in our
	// hex buff
	unsigned char *hex = Malloc(n);
	// add the content toour hex buff
	ReadHexFile(inf, hex);
	// release mem file stream
    fclose(inf);
	// return hex buff
	return hex;
}

