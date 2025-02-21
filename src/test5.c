#include "balloc.h"
#include <stdio.h>

int main() {
  printf("[INFO] testing realloc: ");
  alloc b = {0};
  balloc_init(&b, 1, BALLOC);

  int* a = balloc(&b, sizeof(int) * 22);

  for(int i = 0; i < 22; i++) {
    a[i] = i + 1;
  }

  a = brealloc(&b, a, sizeof(int) * 26);

  for(int i = 0; i < 22; i++) {
    if(a[i] != i + 1) return 1;
  }

  for(int i = 21; i < 26; i++) {
    a[i] = i + 1;
  }

  int* c = balloc(&b, 1);
  (void) c;

  int* tmp = a;
  a = brealloc(&b, a, sizeof(int) * 40);

  if(a == tmp) return 1;

  for(int i = 0; i < 26; i++) {
    if(a[i] != i + 1) return i + 1;
  }

  return 0;
}
