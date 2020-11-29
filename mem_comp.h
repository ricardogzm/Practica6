#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <stdbool.h>
#include <sys/types.h>

int * attachMemoryBlock(int size);
void detachMemoryBlock(int *block);
void destroyMemoryBlock();

#define BLOCK_SIZE sizeof(int)

#endif
