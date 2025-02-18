#ifndef BALLOC_H
#define BALLOC_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  void* mem;
  size_t size;
}alloc;

typedef struct {
  uint32_t idx;
  uint32_t size;
} header;

/// initialise alloc with size (aligned page)
/// size has to be greater than 0
void balloc_init(alloc* b, size_t size);

/// deinitialise alloc, this frees the memory pool
void balloc_deinit(alloc b);

/// reset alloc, frees every element in the memory pool
void breset(alloc* b);

/// allocates an object of size and returns its address
void* balloc(alloc* b, size_t size);

/// frees item in the memory pool
/// the pointer is not invalidated, nor is the address
void bfree(alloc b, void* item);

#endif // BALLOC_H
