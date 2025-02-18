#include "balloc.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  printf("[INFO] testing growth: ");
  const size_t pagesize = getpagesize();

  alloc b = {0};
  balloc_init(&b, 0);

  int64_t* a = balloc(&b, sizeof(int64_t) * pagesize / 8);
  a[0] = 0;

  if(b.size == pagesize) return 1;

  return 0;
}
