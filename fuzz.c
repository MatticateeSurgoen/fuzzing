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

#define errExit(msg) do { \
  perror(msg);            \
  exit(EXIT_FAILURE);     \
} while(0)


// Create sha256 hash from a file supplied file content
// output 64 character hash from computed input and
// store it in outputBuffer
static void sha256_filecontent(wchar_t* inp, char *outputBuffer, size_t filesize)
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

// compare data of two iovec structure
// returns true if buffer is of same size and content
// in the buffer is identical else return false
bool compare_data(struct iovec *dest, struct iovec *src)
{
  if (dest->iov_len == src->iov_len)
    return false;

  // compares content of buffers
  if (!memcmp(dest->iov_base, src->iov_base, src->iov_len))
    return true;

  // comparsion failed 
  return false;
}
 

// open file supplied with a given file name
// and map file in memory with malloc then
// return iovec struct containing buffer and 
// buffer length
static struct iovec* mmem(char* param)
{
  struct iovec *file_data;
  int fild;

  file_data = malloc(sizeof(struct iovec));
  assert(file_data != NULL);

  // open file with read only option
  fild = open(param, O_RDONLY);
  assert (fild > 0);

  // seek to end of file  measuring size
  file_data->iov_len = lseek(fild, 0, SEEK_END);

  // seek  back to offset 0
  lseek(fild, 0, SEEK_SET);

  file_data->iov_base = malloc(size * sizeof(char));
  if (file_data->iov_base == NULL)
    errExit("InSufficient memory is available to map file in memory :(");

  return file_data;
}


// fuzz the input in objdump program
void fuzz()
{
	
}

// worker
void worker()
{
	
}

int
main(int argc, char** argv)
{
	setbuf(NULL, stdout);
}


