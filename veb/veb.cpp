#include "veb.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  VEBTree veb(1 << 16);
  int choice;
  int num, result;

  while (true) {
    system("clear");

    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Successor\n");
    printf("4. Predecessor\n");
    printf("5. Minimum\n");
    printf("6. Maximum\n");
    printf("7. Exit\n");
    printf("Enter your choice(1..7): ");

    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("Enter the element: ");
      scanf("%d", &num);

      veb.insert(num);
      printf("Element inserted ");

      getchar();
      getchar();

      break;
    case 2:
      printf("Enter the element: ");
      scanf("%d", &num);

      veb.remove(num);
      printf("Element removed ");

      getchar();
      getchar();

      break;
    case 3:
      printf("Enter the element: ");
      scanf("%d", &num);

      result = veb.successor(num);

      if (result == -1) {
        printf("Successor not found ");
      } else {
        printf("Successor: %d ", result);
      }

      getchar();
      getchar();

      break;
    case 4:
      printf("Enter the element: ");
      scanf("%d", &num);

      result = veb.predecessor(num);

      if (result == -1) {
        printf("Predecessor not found ");
      } else {
        printf("Predecessor: %d ", result);
      }

      getchar();
      getchar();

      break;
    case 5:
      result = veb.minimum();

      if (result == -1) {
        printf("No minimum element ");
      } else {
        printf("Minimum: %d ", result);
      }

      getchar();
      getchar();

      break;
    case 6:
      result = veb.maximum();

      if (result == -1) {
        printf("No maximum element ");
      } else {
        printf("Maximum: %d ", result);
      }

      getchar();
      getchar();

      break;
    case 7:
      printf("Exiting...\n");
      return 0;
    default:
      printf("Invalid choice ");

      getchar();
      getchar();

      break;
    }
  }
}
