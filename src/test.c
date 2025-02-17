#include "balloc.h"
#include <stdio.h>

int main() {
  alloc b = {0};
  balloc_init(&b);

  char* p = balloc(&b, sizeof(char) * 12);
  sprintf(p, "hello world");

  printf("%s\n", p);

  int* a = balloc(&b, sizeof(int) * 128);

  for(int i = 0; i < 128; i++) {
    a[i] = i;
  }

  int sum = 0;
  for(int i = 0; i < 128; i++) {
    sum += a[i];
  }
  bfree(b, a);

  printf("%d\n", sum);

  char* tmp = p;
  bfree(b, p);

  char* q = balloc(&b, sizeof(char) * 12);
  sprintf(q, "hello world");


  if(tmp == q) printf("%s\n", tmp);

  bfree(b, q);

  balloc_deinit(b);

  return 0;
}
