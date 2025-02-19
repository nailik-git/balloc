#include "balloc.h"
#include <stdint.h>
#include <stdio.h>

typedef struct item {
  int64_t a;
  int64_t b;
  double c;
} item;

int main() {
  printf("[INFO] testing general functionality: ");

  alloc b = {0};
  balloc_init(&b, 1, BALLOC);

  item* array[10];
  
  for(int i = 0; i < 10; i++) {
    array[i] = balloc(&b, sizeof(item));
    array[i]->a = i;
    array[i]->b = i * 2;
    array[i]->c = (double) (i) / 2;
  }

  bfree(b, array[4]);

  int64_t* je = balloc(&b, sizeof(item));

  if(je[0] != 4) return 1;
  if(je[1] != 8) return 1;
  if(*(double*) (&je[2]) != 2.0) return 1;

  bfree(b, array[5]);
  bfree(b, array[6]);
  header* a = (header*) (array[5]) - 1;

  if(a->size == 3) return 1;

  balloc_deinit(b);

  return 0;
}
