#include "veb.hpp"
#include <iostream>

using namespace std;

int main(void) {
  VEBTree veb(16);
  int choice;
  int num, result;

  while (true) {
    system("clear");

    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Successor" << endl;
    cout << "4. Predecessor" << endl;
    cout << "5. Minimum" << endl;
    cout << "6. Maximum" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice(1..7): ";

    cin >> choice;
    switch (choice) {
    case 1:
      cout << "Enter the element: ";
      cin >> num;

      veb.insert(num);
      cout << "Element inserted ";

      getchar();
      getchar();

      break;
    case 2:
      cout << "Enter the element: ";
      cin >> num;

      veb.remove(num);
      cout << "Element removed ";

      getchar();
      getchar();

      break;
    case 3:
      cout << "Enter the element: ";
      cin >> num;

      result = veb.successor(num);

      if (result == -1) {
        cout << "Element not found ";
      } else {
        cout << "Successor: " << result << " ";
      }

      getchar();
      getchar();

      break;
    case 4:
      cout << "Enter the element: ";
      cin >> num;

      result = veb.predecessor(num);

      if (result == -1) {
        cout << "Element not found ";
      } else {
        cout << "Predecessor: " << result << " ";
      }

      getchar();
      getchar();

      break;
    case 5:
      cout << "Minimum: " << veb.minimum() << " ";

      getchar();
      getchar();

      break;
    case 6:
      cout << "Maximum: " << veb.maximum() << " ";

      getchar();
      getchar();

      break;
    case 7:
      cout << "Exiting... " << endl;
      return 0;
    default:
      cout << "Invalid choice ";

      getchar();
      getchar();

      break;
    }
  }
}
