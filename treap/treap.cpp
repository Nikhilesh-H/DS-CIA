#include <stdio.h>

#include "treap.h"

int main()
{
    int choice, key, data;
    treap treap;

    while (1)
    {
        printf("\nMenu:\n");
        printf("\t1. Insert\n");
        printf("\t2. Delete\n");
        printf("\t3. Search\n");
        printf("\t4. Display\n");
        printf("\t5. Exit\n");
        printf("Enter you choice : ");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key : ");
            scanf("%d", &key);

            printf("Enter data : ");
            scanf("%d", &data);

            if (treap.insert(key, data))
            {
                printf("Successfully inserted (%d,%d).\n", key, data);
            }
            else
            {
                printf("Insertion unsuccessfull.\n");
            }

            break;
        case 2:
            printf("Enter key : ");
            scanf("%d", &key);

            if (treap.search(key))
            {
                treap.del(key);
                printf("Successfully deleted %d\n", key);
            }
            else
            {
                printf("%d - Not found.\n", key);
            }

            break;
        case 3:
            printf("Enter key : ");
            scanf("%d", &key);

            if (treap.search(key))
            {
                printf("%d - Found.\n", key);
            }
            else
            {
                printf("%d - Not found.\n", key);
            }

            break;
        case 4:
            treap.display();

            break;
        case 5:
            return 0;
        default:
            printf("Error! Enter a valid choice.\n");
        }
    }
}
