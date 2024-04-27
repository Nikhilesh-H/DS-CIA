#include "veb.h"

#include <stdio.h>

int main(void) {
  VEBTree veb(1 << 16);
  int choice, num, result;

  while (true) {
    system("clear");

    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Search\n");
    printf("4. Successor\n");
    printf("5. Predecessor\n");
    printf("6. Minimum\n");
    printf("7. Maximum\n");
    printf("8. Exit\n");
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

      if (veb.search(num)) {
        printf("Element found ");
      } else {
        printf("Element not found ");
      }

      getchar();
      getchar();

      break;
    case 4:
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
    case 5:
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
    case 6:
      result = veb.getmin();

      if (result == -1) {
        printf("No minimum element ");
      } else {
        printf("Minimum: %d ", result);
      }

      getchar();
      getchar();

      break;
    case 7:
      result = veb.getmax();

      if (result == -1) {
        printf("No maximum element ");
      } else {
        printf("Maximum: %d ", result);
      }

      getchar();
      getchar();

      break;
    case 8:
      printf("Exiting...\n");
      exit(0)
      return 0;
    default:
      printf("Invalid choice ");

      getchar();
      getchar();

      break;
    }
  }
}
