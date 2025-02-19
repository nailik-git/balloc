#include "balloc.h"
#include <stdio.h>
#include <string.h>

int main() {
  printf("[INFO] testing general functionality: ");
  alloc b = {0};
  balloc_init(&b, 1, BALLOC);

  char* p = balloc(&b, sizeof(char) * 12);
  sprintf(p, "hello world");

  if(strcmp(p, "hello world") != 0) return 1;

  int* a = balloc(&b, sizeof(int) * 128);

  for(int i = 0; i < 128; i++) {
    a[i] = i;
  }

  int sum = 0;
  for(int i = 0; i < 128; i++) {
    sum += a[i];
  }
  bfree(b, a);

  if(sum != 8128) return 1;

  bfree(b, p);

  char* q = balloc(&b, sizeof(char) * 12);
  sprintf(q, "Hello World");

  // pointers aren't invalidated so don't do stupid shit
  if(p == q && strcmp(p, "Hello World") != 0) return 1;

  bfree(b, q);

  balloc_deinit(b);

  return 0;
}
