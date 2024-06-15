//Creator: Shao(Shawn) Zhang
//Student ID: 301571321

#include <stdio.h>
#include "list.h"

void ItemFreeFn(void* pItem)
{
    pItem=NULL;
    return;
}

bool Comparator(void* pItem, void* pComparisonArg)
{
    if(pItem==pComparisonArg)
    {
        return 1;
    }

    return 0;
}

int main(){

    // 
    //Tested edge cases before writing the formal test program for the function
    // 



    printf("\n");
    printf("****TEST FOR APPEND AND PREPEND****\n");

    List* list1=List_create();
    char a='a';
    char b='b';
    char c='c';

    //test function calls
    List_append(list1, &a);
    List_append(list1, &b);
    List_prepend(list1, &c);

    printf("After append a, b then prepend c, list1 should have items c a b\n");
    printf("list1: ");
    //print the list and test List_first, List_next and List_last
    printf("%c ", *(char*)List_first(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c\n", *(char*)List_last(list1));
    //test List_curr
    printf("List1 current item is ");
    printf("%c\n", *(char*)List_curr(list1));
    //test List_prev
    printf("List1's previous item of b is ");
    printf("%c\n", *(char*)List_prev(list1));
    printf("List1's previous item of a is ");
    printf("%c\n", *(char*)List_prev(list1));
    //test List_count
    printf("list1 has size ");
    printf("%d", List_count(list1));

    printf("\n\n\n\n");


    printf("****TEST FOR INSERTION****\n");

    List* list2=List_create();
    char d='d';
    char num1='1';
    char e='e';
    char f='f';
    char num2='2';
    char num3='3';

    //test function calls
    List_insert_after(list2, &d);
    List_insert_before(list2, &num1);
    List_insert_after(list2, &e);
    List_insert_after(list2, &f);
    List_insert_before(list2, &num2);
    List_insert_before(list2, &num3);

    printf("After after and before insertions, list2 should have items 1 e 3 2 f d\n");
    printf("list2: ");
    printf("%c ", *(char*)List_first(list2));
    printf("%c ", *(char*)List_next(list2));
    printf("%c ", *(char*)List_next(list2));
    printf("%c ", *(char*)List_next(list2));
    printf("%c ", *(char*)List_next(list2));
    printf("%c\n", *(char*)List_last(list2));
    //test List_first
    printf("list2's first item is ");
    printf("%c\n", *(char*)List_first(list2));
    //test List_last
    printf("list2's last item is ");
    printf("%c\n", *(char*)List_last(list2));   
    //test List_count
    printf("list2 has size ");
    printf("%d", List_count(list2));

    printf("\n\n\n\n");


    printf("****TEST FOR REMOVE AND TRIM****\n");

    //test function calls
    List_trim(list1);

    printf("After trim, the new current item should be a, and list1 should have c a\n");
    //test current item after trim
    printf("list1 current item is ");
    printf("%c\n", *(char*)List_curr(list1));
    //test first and last items after trim
    printf("list1: ");
    printf("%c ", *(char*)List_first(list1));
    printf("%c\n", *(char*)List_last(list1));
    //test List_count
    printf("list1 has size ");
    printf("%d", List_count(list1));

    printf("\n\n");

    //test List_prev
    //move the current pointer away from the end
    void* move1=List_prev(list2);
    void* move2=List_prev(list2);
    void* move3=List_prev(list2);

    //test List_curr
    printf("list2's current item should be 3, and list2's current item will be 2 after removal\n");
    printf("Before removal, list2 current item is ");
    printf("%c\n", *(char*)List_curr(list2));

    //test function call
    List_remove(list2);

    printf("After removal, list2 current item is ");
    printf("%c\n", *(char*)List_curr(list2));
    //print the list and test List_first, List_next and List_last
    printf("list2 should have 1 e 2 f d\n");
    printf("list2: ");
    printf("%c ", *(char*)List_first(list2));
    printf("%c ", *(char*)List_next(list2));
    printf("%c ", *(char*)List_next(list2));
    printf("%c ", *(char*)List_next(list2));
    printf("%c\n", *(char*)List_last(list2));
    //test List_count
    printf("list2 has size ");
    printf("%d", List_count(list2));

    printf("\n\n\n\n");


    printf("****TEST FOR CONCATENATION****\n");

    printf("After concatenate list1 and list2, list2 will disappear and list 1 will have all the items\n");

    //test function call
    List_concat(list1, list2);

    if(List_count(list2)==0)
    {
        //test List_count
        printf("After concatenate, list2's size is ");
        printf("%d", List_count(list2));
    }
    printf("\n");

    //print the list and test List_first, List_next and List_last
    printf("list1 shoould have c a 1 e 2 f d\n");
    printf("list1: ");
    printf("%c ", *(char*)List_first(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c\n", *(char*)List_last(list1));
    //test List_count
    printf("list1 has size ");
    printf("%d", List_count(list1));

    printf("\n\n\n\n");


    printf("****TEST FOR SEARCH****\n");

    printf("Search z, c and 2 in list1. Function should find c and 2, and z is missing\n");
    //print the list and test List_first, List_next and List_last
    printf("list1: ");
    printf("%c ", *(char*)List_first(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c ", *(char*)List_next(list1));
    printf("%c\n", *(char*)List_last(list1));

    //call test function
    char z='z';
    if(List_search(list1, Comparator, &z))
    {
        printf("z is found\n");
    }
    else
    {
        printf("z is not found\n");
    }

    if(List_search(list1, Comparator, &c))
    {
        printf("c is found\n");
    }
    else
    {
        printf("c is not found\n");
    }

    if(List_search(list1, Comparator, &num2))
    {
        printf("2 is found\n");
    }
    else
    {
        printf("2 is not found\n");
    }

    printf("\n\n\n\n");



    printf("****TEST FOR FREE LIST****\n");
    
    //test function call
    List_free(list1, ItemFreeFn);

    //test List_count
    printf("After List_free, list1 has size ");
    printf("%d", List_count(list1));

    printf("\n\n\n\n");
 
    return 0;

    
}