/*******************************************************************************
*                                                                              *
*  RANDOM RAM ACCESS SPEED TEST                                                *
*                                                                              *
*  WILLIAM YAO                                                                 *
*                                                                              *
*******************************************************************************/

                //////////////////////////////////////////////
                // WARNING: REQUIRES 2GB OF FREE RAM TO RUN //
                //////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint64_t state = 0xeca69c3de0d7bf60;
uint64_t a = 0xfea8f5d09d412184;
uint64_t b = 0x763a818bed1aefbe;

uint64_t byte_size(uint64_t size, char type)
{
  switch(type) {
    case 'p':
      size *= 1024;
    case 't':
      size *= 1024;
    case 'g':
      size *= 1024;
    case 'm':
      size *= 1024;
    case 'k':
      size *= 1024;
  }
  
  return size;
}

uint64_t bigrand(uint64_t upper)
{
  state = (state * a) + b;
  return state % upper;
}

int main()
{
  char temp;
  uint64_t i;
  uint64_t total_time = 0;
  uint64_t upper = byte_size(2, 'g');
  uint64_t accesses = byte_size(10, 'm');

  char* bytes = malloc(sizeof(char) * upper);

  for(i = 0; i < accesses; i++) {
    uint64_t index = bigrand(upper);
    clock_t start = clock();
    temp = bytes[index];
    total_time += clock() - start;
  }

  printf("Total time taken for accesses: %lld ms\n", total_time * 1000 / CLOCKS_PER_SEC);

  free(bytes);

  bytes = 0;

  return 0;
}
