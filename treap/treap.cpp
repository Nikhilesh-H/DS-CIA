#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

int main(){
    int choice;
    int key;
    int data;
    treap t;
    while(1){
        printf("\nMenu:\n\t1. Insert\n\t2. Delete\n\t3. Search\n\t4. Display\n\t5. Exit\nEnter you choice : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                printf("Enter key : ");
                scanf("%d",&key);
                printf("Enter data : ");
                scanf("%d",&data);
                if(t.insert(key, data)){
                    printf("Successfully inserted (%d,%d).\n",key,data);
                }
                else{
                    printf("Insertion unsuccessfull.\n");
                }
                break;
            }
            case 2:{
                printf("Enter key : ");
                scanf("%d",&key);
                if(t.search(key)){
                    t.del(key);
                    printf("Successfully deleted %d\n", key);
                }
                else{
                    printf("%d - Not found.\n", key);
                }
                break;
            }
            case 3:{
                printf("Enter key : ");
                scanf("%d",&key);
                if(t.search(key)){
                    printf("%d - Found.\n",key);
                }
                else{
                    printf("%d - Not found.\n", key);
                }
                break;
            }
            case 4:{
                t.display();
                break;
            }
            case 5:{
                t.~treap();
                exit(0);
            }
            default:{
                printf("Error! Enter a valid choice.\n");
            }
        }
    }
    return 0;
}
