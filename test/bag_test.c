#include "../src/data_structures/bag/bag.h"
#include <stdio.h>

int main() {
  bag_t *b = bag_init(5);
  printf("expect the new bag to be empty: %s\n",
         bag_is_empty(b) ? "true" : "false");
  int items[] = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    bag_add(b, &items[i]);
  }
  printf("expect the bag's number of items to be 5: %d\n", bag_size(b));

  if (bag_iter_init(b)) {
    while (bag_iter_has_next(b)) {
      int item;
      bag_iter_next(b, &item);
      printf("%d ", item);
    }
  }

  bag_free(b);
}
