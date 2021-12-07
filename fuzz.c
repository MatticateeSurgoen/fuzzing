
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <openssl/sha.h>
#include <getopt.h>
#include <stddef.h>

// Create sha256 hash from a file supplied file content
void 
sha256_filecontent(wchar_t* inp, char *outputBuffer, size_t filesize)
{
	// stores the hash 
	unsigned char hash[SHA256_DIGEST_LENGTH];

	// sha256 wrapper
	SHA256_CTX sha256;

	// Initialize sha256 with value
	SHA256_Init(&sha256);

	// update sha256 with our input string
	SHA256_Update(&sha256, inp, filesize);
	
	// Generate hex value from character bytes
	for (register int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}
	outputBuffer[64] = '\0';
}

/* 
maps file in memory
copy data file in memory
and write address to 
*/
void* mmem(char* param)
{
    // open file with read only option
    int fd = open(param, O_RDONLY);
    if (fd == -1) 
    {   
        perror("program doesn't able to map file in memory\n");
        exit(EXIT_FAILURE);
    }   

    // seek to end of file  measuring size
    size_t size = lseek(fd, 0, SEEK_END);

    // seek  back to offset 0
    lseek(fd, 0, SEEK_SET);

    // map file in with mmap
    if ((addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {   
        perror("not able to map in memory mmap error\n");
        exit(EXIT_FAILURE);
    }   
    close(fd);

    return (void*)&addr;
}


// fuzz the input in objdump program
void 
fuzz()
{
	
}

// worker
void 
worker
{
	
}

int
main(int argc, char** argv)
{
	setbuf(NULL, stdout);
}


