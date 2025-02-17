#ifndef BALLOC_H
#define BALLOC_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
  void* mem;
  size_t size;
}alloc;

typedef struct {
  uint32_t idx;
  uint32_t size;
} header;

void balloc_init(alloc* b);
void balloc_deinit(alloc b);

void breset(alloc* b);

void* balloc(alloc* b, size_t size);
void bfree(alloc b, void* item);

#endif // BALLOC_H
