CC = gcc
CFLAGS = -c -std=gnu11 -g -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wmissing-prototypes -Wmissing-declarations -Winline -Wlong-long -Wuninitialized -Wconversion -Wstrict-prototypes -Wno-variadic-macros
LINK_FLAGS = -lcrypto -ldl
LIBS = $(wildcard lib/*.c)
OBJECT = $(wildcard build/*.o)
BUILD_PATH = build/

link: compile
		cd build/
		$(CC) $(LINK_FLAGS) $(OBJECT) bin/main.o  -o bin/main
		rm -rf bin/*.o
compile:
		$(CC) $(CFLAGS) $(LIBS)
		mv *.o $(BUILD_PATH)
		#compile client and server objects
		$(CC) $(CFLAGS) main.c
		mv *.o bin/
run:
		./bin/main aes_128_ecb
		./bin/main aes_128_cbc
clean:
		rm -rf build/*.o
		rm -rf *.o
		rm -rf bin/*
mem:
	#=======================================================================================
	valgrind ./bin/main aes_128_ecb
	#=======================================================================================
	valgrind ./bin/main aes_128_cbc
	#=======================================================================================
