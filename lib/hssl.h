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


#ifndef HSSL_H
#define HSSL_H

/**
 * Include all dyncamic sys libs
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <locale.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
/**
 * Include require
 * open ssl func for EVP
 * NOTE that openssl/evp
 * include all sort of openssl libs
 * like openssl/opensslconf.h, openssl/ossl_typ
 * openssl/symhacks.h
 */

#include <openssl/evp.h>
/**
 * Debug functions prototypes
 * These functions help us to debug some sort 
 * of things we are interested
 */
void		print_file_content(const char *);
void		info(const char *,const char *, const unsigned char *);
void		break_intr(const int, const int);
void		enter(const char *, const size_t);
void		output(const void *, const size_t, bool );
/**
 * Color pallet macros
 */
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"
//
//GLOBALS
//
//
#define CHUNK 1024
char *plain_text;
char *algorithm_type;
unsigned char *crypto_text;
/**
 * Target global path 
 */

//global plaintext
#define PLAINTEXT_PATH "test_files/plaintext.txt"
// ecb targets
#define ALG_PATH_ECB "test_files/alg.txt"
#define CRYPTOTEXT_PATH_ECB "test_files/cryptotext.txt"
// cbc targets
#define ALG_PATH_CBC "test_files/alg1.txt"
#define CRYPTOTEXT_PATH_CBC "test_files/cryptotext1.txt"
/**
 * In case these macros are not define
 * in the sys files define it
 */
#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE -1
#endif
/**
 * Prototype for our own
 * function that handles error
 * and output it to the stdout stream
 */
void		echo_error(const char*,bool, int);
void		prog_error(const char*, bool, int);

/**
 * Prototype for our own
 * wrapper sys functions
 */
void		*Malloc(size_t);
char		*Fgets(char*, int, FILE*);
void		Fputs(const char*, FILE*);
void		Fclose(FILE *);
FILE		*Fopen(const char *, const char*);
int			Fseek(FILE *, long int, int);
long int	Ftell(FILE*);
size_t		Fread(void*, size_t, size_t, FILE*);
/**
 * Prototype for 
 * main core func
 */
char			*load_from_file(const char *);
unsigned char	*encrypt(unsigned char*, const EVP_CIPHER *);
bool			is_equal(unsigned char *, unsigned char *);
unsigned char	*load_from_file_hex(const char*);
unsigned char*	prepare_sanitize_key(const char*);
void			alloc_globals(const char*,const char*, const char *);
void			free_globals(void);
void			mechanism(const char*, const char*, const EVP_CIPHER *);
#endif

