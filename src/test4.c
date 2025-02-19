#include "balloc.h"
#include <stdint.h>
#include <stdio.h>

int main() {
  printf("[INFO] testing multiple allocators: ");

  alloc b1 = {0};
  alloc b2 = {0};

  balloc_init(&b1, sizeof(int64_t) * 1024 + 1, BALLOC);
  int64_t* a = balloc(&b1, sizeof(int64_t) * 1024);
  a[0] = 'a';
  a[1023] = 'd';

  balloc_init(&b2, sizeof(int64_t) * 2048 + 1, BARENA);
  int64_t* b = balloc(&b2, sizeof(int64_t) * 2048);
  b[0] = 'b';
  b[2047] = 'e';

  int64_t* c = balloc(&b1, sizeof(int64_t) * 1024);
  c[0] = 'c';
  c[1023] = 'f';

  for(int i = 0; i < 2048; i++) {
    if(b[i] == 'c' || b[i] == 'f') return 1;
  }

  return 0;
}
