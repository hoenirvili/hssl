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

#include "lib/hssl.h"
// time values
clock_t begin, end;
double time_spent;

int
main(int argc, char *argv[])
{
	// for formatting reasons
	printf("\n");
	// if we don't have any commands to parse
	// just exit
	if(argc < 2) {
		fprintf(stderr,"./main [command]\n");
		fprintf(stderr,"aes_128_ecb/aes_128_cbc\n");
		exit(EXIT_SUCCESS);
	}
	// Start bruteforcing for aes_128_ecb 
	// finding the correct key
	if((strncmp(argv[1], "aes_128_ecb", 11) == 0)) {
		begin = clock();
		mechanism(ALG_PATH_ECB ,CRYPTOTEXT_PATH_ECB, EVP_aes_128_ecb());
		end = clock();
		time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
		printf("\n\n");
		fprintf(stdout, KGRN"\tTIME EXECUTION : "KWHT"%F\n",time_spent);
		printf("\n");
	}
	// start bruteforcing for aes_128_cbc
	// finding the correct key
	if((strncmp(argv[1], "aes_128_cbc", 11) == 0)) {
		begin = clock();
		mechanism(ALG_PATH_CBC ,CRYPTOTEXT_PATH_CBC, EVP_aes_128_cbc());
		end = clock();
		time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
		printf("\n\n");
		fprintf(stdout, KGRN"\tTIME EXECUTION : "KWHT"%F\n",time_spent);
		printf("\n");
	}
}
