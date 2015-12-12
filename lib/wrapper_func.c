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
/*
 * Our own stadard I/O wrapper functions
 * from stdin
 */
char *
Fgets(char *ptr, int n, FILE* stream)
{
	char *fpointer = fgets(ptr, n, stream);
	int file_error = ferror(stream);

	//if fgets returns null and ferror retun true
	if((fpointer == NULL) && (file_error)) {
		echo_error("Can't read line from stdin",true, errno);
		return NULL;
	}
	return fpointer;

}

void
Fputs(const char *ptr, FILE*stream)
{
	if(fputs(ptr,stream) == EOF) {
		prog_error("Can't output line from buffer ", true, errno);
	}
}

FILE *
Fopen(const char *path, const char *mode)
{
	FILE *rfile = fopen(path, mode);
	char msg[100];
	if(rfile== NULL) {
		if(sprintf(msg, "Can't open this stream %s",path))
			prog_error(msg, true, errno);
		else 
			prog_error("Can't open this stream ", true, errno);
	} 

	return rfile;
}

void
Fclose(FILE *stream)
{
	int rclose= fclose(stream);
	if(rclose != 0) {
		prog_error("Can't close the stream", true, errno);
	}
}

int 
Fseek(FILE *stream, long int offset, int whence)
{
	int rsk;
	rsk = fseek(stream, offset, whence);
	if(rsk != 0) {
		prog_error("Can't set file cursor", true, errno);
	}
	
	return rsk;
}

// long or long int are identical but i rather keep it like
// ftell prototype definition by POSSIX standard
long int
Ftell(FILE *stream)
{
	long rft = ftell(stream);
	if( rft == -1L) {
		prog_error("Can't return filesize", true, errno);
	}

	return rft;
}

size_t
Fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t rfrd = fread(ptr, size, nmemb, stream);
	// something to consider if we already reach the end of the file
	// should be treated or something else just output error
	if( rfrd != nmemb) {
		prog_error("Error reading the file", true, errno);
	}

	return rfrd;
}
/**
 * stdlib malloc wrapper func
 */
void *
Malloc(size_t size)
{
	void *ptr = malloc(size);
	if(ptr == NULL)
		prog_error("Unable to allocate memory, ", true, errno);
	return ptr;
}


