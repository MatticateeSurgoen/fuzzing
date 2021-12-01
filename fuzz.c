
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
void sha256_filecontent(wchar_t* inp, char *outputBuffer, size_t filesize)
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

int
main(int argc, char** argv)
{
	
}
