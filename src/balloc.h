#ifndef BALLOC_H
#define BALLOC_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
  BALLOC,
  BARENA
} alloc_type;

typedef struct {
  void* mem;
  size_t size;
  size_t idx;
  alloc_type type;
} alloc;

typedef struct {
  uint32_t idx;
  uint32_t size;
} header;

/// initialise alloc of type with size (aligned page)
/// size has to be greater than 0
/// type can be BALLOC or BARENA
void balloc_init(alloc* b, size_t size, alloc_type type);

/// deinitialise alloc, this frees the memory pool
void balloc_deinit(alloc b);

/// reset alloc, frees every element in the memory pool
void breset(alloc* b);

/// allocates an object of size and returns its address
void* balloc(alloc* b, size_t size);

/// frees item in the memory pool (only works for type BALLOC)
/// the pointer is not invalidated, nor is the address
void bfree(alloc b, void* item);

#endif // BALLOC_H
