#include "balloc.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  printf("[INFO] testing growth: ");
  const size_t pagesize = getpagesize();

  alloc b = {0};
  balloc_init(&b, 1, BARENA);

  int64_t* a = balloc(&b, sizeof(int64_t) * pagesize / 8 + 1);
  a[0] = 0;

  if(b.size == pagesize) return 1;

  balloc_deinit(b);
  balloc_init(&b, 1, BALLOC);

  if(b.mem != (void*) 0x100000000) return 1;

  a = balloc(&b, sizeof(int64_t) * pagesize / 8 + 1);
  a[0] = 0;

  if(b.size == pagesize) return 1;

  return 0;
}
