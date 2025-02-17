#include "balloc.h"
#include <assert.h>

void balloc_init(alloc* b) {
  b->mem = malloc(8 * 256);
  assert(b->mem != NULL && "buy more RAM lol");
  b->size = 8 * 256;
  ((header*)b->mem)->idx = 0;
  ((header*)b->mem)->size = 255;
}

void balloc_deinit(alloc b) {
  free(b.mem);
  b.size = 0;
}

void breset(alloc* b) {
  header* h = (header*) (b->mem);
  *h = (header) {.idx = 0, .size = b->size / 8 - 1};
}

void* balloc(alloc* b, size_t size) {
  const size_t mod8 = size % 8;
  const size_t new_size = size + (mod8 ? 8 - mod8 : 0);
  const size_t div8 = new_size / 8;

  void* r = NULL;
  size_t i = 0;

  do {
    header* cur = (header*) (b->mem) + i;

    if(cur->size > div8) {
      r = cur + 1;
      header* new = cur + 1 + div8;
      *new = (header) {.idx = cur->idx, .size = cur->size - 1 - div8};
      *cur = (header) {.idx = i + 1 + div8, .size = 0};
      break;
    } else if(cur->size == size) {
      r = (header*) (b->mem) + 1;
      cur->size = 0;
      break;
    }

    i = cur->idx;
  } while(i != 0);

  return r;
}

void bfree(alloc b, void* item) {
  header* prev = (header*) (b.mem);

  while((header*) (b.mem) + prev->idx + 1 != item) {
    prev = (header*) (b.mem) + prev->idx;
  }
  header* this = (header*) (b.mem) + prev->idx;
  header* next = (header*) (b.mem) + this->idx;

  this->size = this->idx - prev->idx - 1;

  if(this->idx && next->size) {
    this->idx = next->idx;
    this->size += next->size + 1;
  } if(prev->idx && prev->size) {
    prev->idx = this->idx;
    prev->size += this->size + 1;
  }
}

