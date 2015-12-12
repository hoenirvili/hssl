# Bruteforce key test case

Sarcina consta intr-un **bruteforce** pe o cheie. De la inceput se se cunosc urmatoarele:
- cheia contine 16 caractere(16 bytes).
- cheia provine dintr-un [dictionar](http://profs.info.uaic.ro/~olgai/si2015/cripto/word_dict.txt) de cuvinte de origine englez. 
- unul dintre cuvintele din acel dinctionar poate fi mai mic sau egal de 16 caratere 
    - in acest caz se va adauga spatii ( **ASCI** 32 / **HEX** 0x20) pana la umplerea cheii.
- algoritmi de criptare folositi:
    - **aes_128_ecb**
    - **aes_128_cbc**

Pentru a simplifica foarte mult codul s-a folosit o libarie open-source **openssl 1.0.2.e-1**.
# Encriptia
Toata treaba pentru encriptie consta in functia urmatoare cu prototipul.
```c
unsigned char* encrypt (unsigned char *key, const EVP_CIPHER *algo_type)
```
Aceasta functie ia ca parametru un pointer la o cheie de tip `unsigned char` (valori pozitive, fara bitul de semn, 0-255).
Folosind acest tip vom reprezenta fiecare bit in forma 0xff, 0x22 etc.Daca foloseam tipul `char` acest tip e paddat adica foloseste abolut toti 8 biti , bitul de semn si cei 7 biti, folosind functii gen ` printf("%x ",mychar); ` puten observa cum afiseaza pe cei 8 biti chiar daca avem valori mici si nu trebuie atasati si nu sub forma de 2 de cat avem nevoie. Al doilea parametru fiind un pointer la o functie de tip `const EVP_CIPHER` aratand ca pointerul in planul nostru de executie nu se modifica, facand astfel memorarea sa spatiul dedicat constantelor.
**Funcia returneaza  un buffer criptat.**

##### Observatie
* Tipul `char` e un tip distinct fata de tipul `unsigned char` si `signed char`
    * `unsigned char` [0..255]
    * `signed char` [-127..127]
    * `char` poate fi de la [0..127] [-127..127] depinde de arhitectura foarte mult.


Programul primeste ca argumente tipul arlgoritmului cu care vrem sa testam **bruteforce-ul**
- aes_128_ecb
- aes_128_cbc

```c
if(argc < 2) {
		fprintf(stderr,"./main [command]\n");
		fprintf(stderr,"aes_128_ecb/aes_128_cbc\n");
		exit(EXIT_SUCCESS);
	}
	// Start bruteforcing for aes_128_ecb 
	// finding the correct key
	if((strncmp(argv[1], "aes_128_ecb", 11) == 0)) {
        //code..
    }
    // start bruteforcing for aes_128_cbc
	// finding the correct key
	if((strncmp(argv[1], "aes_128_cbc", 11) == 0)) {
	    //code..
	}
```
# Timpul
Timpul executiei este cronometrat.
In acest mod vom observa daca pe baza librariei este vreo diferenta majora in algoritmi.

Variabila  `time_spent` va stoca durata planului de executie.
```c
// time values
clock_t begin, end;
double time_spent;

//code

begin = clock();
mechanism(ALG_PATH_ECB ,CRYPTOTEXT_PATH_ECB, EVP_aes_128_ecb());
end = clock();
//code
time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
```

# Memorie
Evident ca vom aduce in discutie memoria, fiind un element esential pentru orice dezvoltator de software care se respecta.
In planul nostru de executie programul face diferite alocari.
Alocarile de start sunt alocarile de buffere de continut.Aceste buffere fiind continutul fisierului cu plain text, fiesierul care contine cripto textul initial si tipul algoritmului de encriptie folosit.
```c
void alloc_globals(const char *ppath, const char* algpath, const char* crypto_path) {
	//ALLOC MEMORY BLOCKS
	plain_text = load_from_file(ppath);
	algorithm_type = load_from_file(algpath);
	crypto_text = load_from_file_hex(crypto_path);
```
Functiile
```c
char *laod_from_file(const char* path);
unsigned char * load_from_file_hex(const char* path);
```
Aloca un buffer de dimensiune dinamica in functie de marimea fisierelor, pentru a putea introduce tot continutul aceste functii returnand un tip de data specific pentru computatia respectiva.

Logic daca aloca trebuie sa eliberam la final de executie memoria.
```c
void free_globals(void)
{
	//free up the memory
	free(plain_text);
	free(algorithm_type);
	free(crypto_text);
}
```
Totusi cea mai mare parte din alocari se petrece secvential pe parcursul **bruteforce-ului** nostru.Deoarece, mereu vom aloca cate o cheie noua in funtie de fiecare cuvant din dictionarul englez stabilit mai sus. Trebuie sa avem grija ca dupa ce folosim memoria sa o eliberam la fel secvential. **De ce nu toata la final?** Pentru ca programul nostru ar suferii mari pierderi de memorie si ar aloca mult prea multa. Un caz nefericit, dictionarul avand peste 50000 de linii(cuvinte) asta inseamna 50000 de mii de alocari si de asta pe parcurs la o alocare trebuie sa existe si o eliberare de memorie.

Un cod ar fi in felul urmator
```c
//code
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
			// or if could just at the begiging memset it to 0x20 all the 16 byts of the key
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
// more code
```
### Valgrind

Programul dupa o executie a lui Valgrind.
```
valgrind ./bin/main aes_128_cbc
==10913== Memcheck, a memory error detector
==10913== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==10913== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==10913== Command: ./bin/main aes_128_cbc
==10913== 
==10913== 
==10913== HEAP SUMMARY:
==10913==     in use at exit: 0 bytes in 0 blocks
==10913==   total heap usage: 37,835 allocs, 37,835 frees, 5,600,818 bytes allocated
==10913== 
==10913== All heap blocks were freed -- no leaks are possible
==10913== 
==10913== For counts of detected and suppressed errors, rerun with: -v
==10913== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
> Dupa cum se se vede in test programul nu sufera de scurgeri de memorie si nici de scrieri sau citiri de memorie nealocata.

# Final
Pentru test am introdus un **Makefile**

Pentru a compila executati comanda 
```
make
```
Dupa compilare rulati cu comanda
```
make run
```
Pentru raportul de memorie rulati comanda
```
make mem
```

# Stdout
```c
┌─╼ [~/Work/hssl]
└────╼ make run
./bin/main aes_128_ecb


PLAINTEXT
This is a top secret.
ALGO TYPE : aes-128-ecb
CRYPTOTEXT
8d 20 e5 5 6a 8d 24 d0 46 2c e7 4e 49 4 c1 b5 f a5 f2 57 c 36 71 d 4d 6a 45 d3 3f c3 bd 53 

Found a match

Length: 16
Content char: median          
Content ASCI: 109 101 100 105 97 110 32 32 32 32 32 32 32 32 32 32 
Content HEX: 6d 65 64 69 61 6e 20 20 20 20 20 20 20 20 20 20 

	TIME EXECUTION : 0.018282

./bin/main aes_128_cbc

PLAINTEXT
This is a top secret.
ALGO TYPE : aes-128-cbc
CRYPTOTEXT
8c a7 1e 74 d1 96 88 7a 7a e7 dc be d7 5c fa 56 4e 2a cd 38 71 d2 fb b6 29 fa ca 25 d6 30 cb 44 

Found a match

Length: 16
Content char: remember        
Content ASCI: 114 101 109 101 109 98 101 114 32 32 32 32 32 32 32 32 
Content HEX: 72 65 6d 65 6d 62 65 72 20 20 20 20 20 20 20 20 

	TIME EXECUTION : 0.011165

```
