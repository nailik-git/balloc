#include "balloc.h"
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>

void balloc_init(alloc* b, size_t size) {
  assert(size != 0 && "size needs to be greater than 0");

  const size_t pagesize = getpagesize();
  const size_t asize = (size + pagesize - 1) & ~(pagesize - 1);
  void* p = (void*) 0x100000000;

  loop:
  b->mem = mmap(
    p,
    asize,
    PROT_READ | PROT_WRITE,
    MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE,
    -1,
    0
  );

  if(b->mem == MAP_FAILED) {
    p = (void*) ((uint64_t) (p) << 1);
    goto loop;
  }

  b->size = asize;
  ((header*)b->mem)->idx = 0;
  ((header*)b->mem)->size = asize / 8 - 1;
}

void balloc_deinit(alloc b) {
  munmap(b.mem, b.size);
}

void breset(alloc* b) {
  header* h = (header*) (b->mem);
  *h = (header) {.idx = 0, .size = b->size / 8 - 1};
}

void* balloc(alloc* b, size_t size) {
  const size_t asize = (size + 7) & ~7;
  const size_t div8 = asize / 8;

  const size_t pagesize = getpagesize();

  void* r = NULL;
  size_t i = 0;
  header* cur;

  loop:
  do {
    cur = (header*) (b->mem) + i;

    if(cur->size > div8) {
      r = cur + 1;
      header* new = cur + 1 + div8;
      *new = (header) {.idx = cur->idx, .size = cur->size - 1 - div8};
      *cur = (header) {.idx = i + 1 + div8, .size = 0};
      break;
    } else if(cur->size == div8 && cur->idx) {
      r = cur + 1;
      cur->size = 0;
      break;
    }

    i = cur->idx;
  } while(i);

  if(r == NULL) {

    void* tmp = mmap(
      b->mem + b->size,
      pagesize,
      PROT_READ | PROT_WRITE,
      MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE,
      -1,
      0
    );
    if(tmp == MAP_FAILED) return r;

    b->size += pagesize;
    cur->size += pagesize / 8;

    goto loop;
  }

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

