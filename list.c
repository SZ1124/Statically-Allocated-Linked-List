//Creator: Shao(Shawn) Zhang
//Student ID: 301571321

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

// General Error Handling:
// Client code is assumed never to call these functions with a NULL List pointer, or 
// bad List pointer. If it does, any behaviour is permitted (such as crashing).
// HINT: Use assert(pList != NULL); just to add a nice check, but not required.

//ALL GLOBAL VARIABLES ARE STATIC
//list array with current empty list ready to be filled and array size
static List Lists[LIST_MAX_NUM_HEADS];
static List* currAvailList;
static int listsSize=0;

//list array with current empty node ready to be filled and array size
static Node Nodes[LIST_MAX_NUM_NODES];
static Node* currAvailNode;
static int nodesSize=0;



// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.

List* List_create()
{
    //1. List is full, return NULL pointer
    if(listsSize==LIST_MAX_NUM_HEADS)
    {
        return NULL;
    }
    
    //2. first time creating list, link all the lists and nodes up and set up next availables,
    // so dont need to find the next availble index when insert and delete
    if(listsSize==0)
    {
        for(int j=0; j<LIST_MAX_NUM_NODES-1; j++)
        {
            Nodes[j].nextAvailNode=&Nodes[j+1];
        }

        for(int i=0; i<LIST_MAX_NUM_HEADS-1; i++)
        {
            Lists[i].nextAvailList=&Lists[i+1];
        }

        //set current available position in array
        currAvailNode=&Nodes[0];
        currAvailList=&Lists[0];
    }

    //initialize new list 
    List* newList;
    newList->size=0;
    newList->head=NULL;
    newList->tail=NULL;
    newList->curr=NULL;
    newList->oobState=2;

    //Make the new list uses current available list array space
    newList=currAvailList;
    currAvailList=currAvailList->nextAvailList;
    listsSize++; //increase array size

    return newList;

}

// Returns the number of items in pList.
int List_count(List* pList)
{
    return pList->size;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList)
{
    if(pList->size==0)
    {
        pList->curr=NULL;
        return NULL;
    }

    //Reset out of bond state
    pList->oobState=2;
    pList->curr=pList->head;
    return pList->head->item;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList)
{
    if(pList->size==0)
    {
        pList->curr=NULL;
        return NULL;
    }

    //Reset out of bond state
    pList->oobState=2;
    pList->curr=pList->tail;
    return pList->tail->item;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList)
{
    //1.empty list
    if(pList->size==0)
    {
        return NULL;
    }//2.current item is at the list's tail
    else if(pList->curr==pList->tail)
    {
        pList->oobState=LIST_OOB_END;
        return NULL;
    }//3.current list is beyond head, so the new current item will be head
    else if(pList->oobState==LIST_OOB_START)
    {
        pList->oobState=2;
        pList->curr=pList->head;
        return pList->curr->item;
    }

    //4.normal case
    pList->curr=pList->curr->next;
    return pList->curr->item;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList)
{
    //1.empty list
    if(pList->size==0)
    {
        return NULL;
    }//2.current item is at the list's head
    else if(pList->curr==pList->head)
    {
        pList->oobState=LIST_OOB_START;
        return NULL;
    }//3.current list is beyond tail, so the new current item will be tail
    else if(pList->oobState==LIST_OOB_END)
    {
        pList->oobState=2;
        pList->curr=pList->tail;
        return pList->curr->item;
    }

    //4.normal case
    pList->curr=pList->curr->prev;
    return pList->curr->item;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList)
{
    return pList->curr->item;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem)
{
    //1. Failure if the node array is full
    if(nodesSize==LIST_MAX_NUM_NODES)
    {
        return -1;
    }

    //plug the item to the current node and make sure its other members are NULL
    currAvailNode->item=pItem;
    currAvailNode->prev=NULL;
    currAvailNode->next=NULL;
    
    //2. empty list
    if(pList->size==0)
    {
        pList->head=currAvailNode;
        pList->tail=currAvailNode;
        pList->curr=currAvailNode;
    }//3. current item is beyond the start
    else if(pList->oobState==LIST_OOB_START)
    {
        pList->head->prev=currAvailNode;
        currAvailNode->next=pList->head;
        pList->head=currAvailNode;
        pList->curr=currAvailNode;
    }//4. current item is beyond the end
    else if(pList->oobState==LIST_OOB_END)
    {
        pList->tail->next=currAvailNode;
        currAvailNode->prev=pList->tail;
        pList->tail=currAvailNode;
        pList->curr=currAvailNode;
    }//5. only one item in the list
    else if(pList->size==1)
    {
        pList->tail->next=currAvailNode;
        currAvailNode->prev=pList->tail;
        pList->tail=currAvailNode;
        pList->curr=currAvailNode;
    }//6. current item is at the tail
    else if(pList->curr==pList->tail)
    {
        pList->tail->next=currAvailNode;
        currAvailNode->prev=pList->tail;
        pList->tail=currAvailNode;
        pList->curr=currAvailNode;
    }//7. normal case
    else
    {
        currAvailNode->next=pList->curr->next;
        currAvailNode->prev=pList->curr;
        pList->curr->next->prev=currAvailNode;
        pList->curr->next=currAvailNode;
        pList->curr=currAvailNode;
    }

    //increase the array index and the list's size, reset out of bond state
    nodesSize++;
    pList->size++;
    pList->oobState=2;
    //move current available node to the next available node
    currAvailNode=currAvailNode->nextAvailNode;

    return 0;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem)
{
    //1. Failure if the node array is full
    if(nodesSize==LIST_MAX_NUM_NODES)
    {
        return -1;
    }

    //plug the item to the current node and make sure its other members are NULL
    currAvailNode->item=pItem;
    currAvailNode->prev=NULL;
    currAvailNode->next=NULL;
    
    //2. empty list
    if(pList->size==0)
    {
        pList->head=currAvailNode;
        pList->tail=currAvailNode;
        pList->curr=currAvailNode;
    }//3. current item is beyond the start
    else if(pList->oobState==LIST_OOB_START)
    {
        pList->head->prev=currAvailNode;
        currAvailNode->next=pList->head;
        pList->head=currAvailNode;
        pList->curr=currAvailNode;
    }//4. current item is beyond the end
    else if(pList->oobState==LIST_OOB_END)
    {
        pList->tail->next=currAvailNode;
        currAvailNode->prev=pList->tail;
        pList->tail=currAvailNode;
        pList->curr=currAvailNode;
    }//5. only one item in the list 
    else if(pList->size==1)
    {
        pList->head->prev=currAvailNode;
        currAvailNode->next=pList->head;
        pList->head=currAvailNode;
        pList->curr=currAvailNode;
    }//6. current item is at the head
    else if(pList->curr==pList->head)
    {
        pList->head->prev=currAvailNode;
        currAvailNode->next=pList->head;
        pList->head=currAvailNode;
        pList->curr=currAvailNode;
    }//7. normal case
    else
    {
        currAvailNode->prev=pList->curr->prev;
        currAvailNode->next=pList->curr;
        pList->curr->prev->next=currAvailNode;
        pList->curr->prev=currAvailNode;
        pList->curr=currAvailNode;
    }

    //increase the array index and the list's size, reset out of bond state
    nodesSize++;
    pList->size++;
    pList->oobState=2;
    //move current available node to the next available node
    currAvailNode=currAvailNode->nextAvailNode;

    return 0;
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem)
{
    //1. Failure if the node array is full
    if(nodesSize==LIST_MAX_NUM_NODES)
    {
        return -1;
    }

    //plug the item to the current node and make sure its other members are NULL
    currAvailNode->item=pItem;
    currAvailNode->prev=NULL;
    currAvailNode->next=NULL;

    //2. empty list
    if(pList->size==0)
    {
        pList->head=currAvailNode;
        pList->tail=currAvailNode;
        pList->curr=currAvailNode;
    }//3. normal case
    else
    {
        //switch the new node with the tail
        currAvailNode->prev=pList->tail;
        pList->tail->next=currAvailNode;
        pList->tail=currAvailNode;
        pList->curr=pList->tail;
    }
    //increase the array index and the list's size, reset out of bond state
    nodesSize++;
    pList->size++;
    pList->oobState=2;
    //move current available node to the next available node
    currAvailNode=currAvailNode->nextAvailNode;

    return 0;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem)
{
    //1. Failure if the node array is full
    if(nodesSize==LIST_MAX_NUM_NODES)
    {
        return -1;
    }

    //plug the item to the current node and make sure its other members are NULL
    currAvailNode->item=pItem;
    currAvailNode->prev=NULL;
    currAvailNode->next=NULL;
    
    //2. empty list
    if(pList->size==0)
    {
        pList->head=currAvailNode;
        pList->tail=currAvailNode;
        pList->curr=pList->head;    
    }//3. normal case
    else
    {
        //switch the new node with the head
        currAvailNode->next=pList->head;
        pList->head->prev=currAvailNode;
        pList->head=currAvailNode;
        pList->curr=pList->head;
    }
    //increase the array index and the list's size, reset out of bond state
    nodesSize++;
    pList->size++;
    pList->oobState=2;
    //move current available node to the next available node
    currAvailNode=currAvailNode->nextAvailNode;

    return 0;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList)
{
    //1. list is in out of bond state
    if(pList->oobState==LIST_OOB_START || pList->oobState==LIST_OOB_END)
    {
        return NULL;
    }//2. empty list
    else if(pList->size==0)
    {
        return NULL;
    }

    void* returnItem=pList->curr->item;

    //shift the current available node because the current plist node is becoming current availble node
    pList->curr->nextAvailNode=currAvailNode;
    currAvailNode=pList->curr;

    //3. only one item in the list
    if(pList->size==1)
    {
        pList->size--;
        pList->head==NULL;
        pList->tail==NULL;

        //empty the new available node
        pList->curr->item=NULL;
        pList->curr->prev=NULL;
        pList->curr->next=NULL;
        pList->curr=NULL;

        pList->oobState==2;
    }//4. current item point to the head
    else if(pList->curr==pList->head)
    {
        pList->head=pList->head->next;

        //empty the new available node
        pList->head->prev->item=NULL;
        pList->head->prev->prev=NULL;
        pList->head->prev->next=NULL;
        pList->head->prev=NULL;

        pList->curr=pList->head;
    }//5. current item point to the tail
    else if(pList->curr==pList->tail)
    {
        pList->tail=pList->tail->prev;

        //empty the new available node
        pList->tail->next->item=NULL;
        pList->tail->next->prev=NULL;
        pList->tail->next->next=NULL;
        pList->tail->next==NULL;

        pList->curr=pList->tail;
    }//6. normal case
    else
    {
        //Isolate the current node and link the nodes up before the removal
        pList->curr->next->prev=pList->curr->prev;
        pList->curr->prev->next=pList->curr->next;
        
        Node* temp=pList->curr->next;
        
        //empty the new available node
        pList->curr->item=NULL;
        pList->curr->prev=NULL;
        pList->curr->next=NULL;
        pList->curr=NULL;

        pList->curr=temp;
    }
    //decrease size
    pList->size--;
    nodesSize--;

    return returnItem;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList)
{
    //1. empty list
    if(pList->size==0)
    {
        return NULL;
    }

    void* returnItem=pList->tail->item;

    //set the current available node to the trimmed tail node
    pList->tail->nextAvailNode=currAvailNode;
    currAvailNode=pList->tail;

    //2. only one item in the list
    if(pList->size==1)
    {
        pList->head==NULL;

        //empty the new available node
        pList->tail->item=NULL;
        pList->tail->prev=NULL;
        pList->tail->next=NULL;
        pList->tail==NULL;

        pList->curr==NULL;
        pList->oobState==2;
    }//3. normal case
    else
    {
        //Mark the new tail
        pList->tail=pList->tail->prev;

        //empty the new available node
        pList->tail->next->item=NULL;
        pList->tail->next->prev=NULL;
        pList->tail->next->next=NULL;
        pList->tail->next==NULL;

        pList->curr=pList->tail;
    }
    //decrease size
    pList->size--;
    nodesSize--;

    return returnItem;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2)
{
    //1. when plist1 is empty, plist2 become plist1
    if(pList1->size==0)
    {
        pList1->size=pList2->size;
        pList1->head=pList2->head;
        pList1->tail=pList2->tail;
        pList1->curr=pList2->curr;
    }//2.when plist2 is empty, so add nothing
    else if(pList2->size==0)
    {
        return;
    }//3. normal case
    else
    {
        pList1->size=(pList1->size)+(pList2->size);
        //link the list tail to head up
        pList1->tail->next=pList2->head;
        pList2->head->prev=pList1->tail;
        pList1->tail=pList2->tail;
    }
    
    //Delete plist2 at the end
    pList2->size=0;
    pList2->head=NULL;
    pList2->tail=NULL;
    pList2->curr=NULL;
    pList2->nextAvailList=currAvailList;
    currAvailList=pList2;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn)
{
    //Start from the first node
    Node* temp=pList->head;

    //traverse through the list to free items
    while(temp!=NULL)
    {
        (*pItemFreeFn)(temp->item);
        temp->next=NULL;
        temp->nextAvailNode=currAvailNode;
        currAvailNode=temp;

        temp=temp->next;
    }
    //As instruction mentioned "its head and nodes are available for future operations",
    //does not need to free the  struct List_s* next  pointer
    //decrease the list array size and empty the list
    listsSize--;
    pList->size=0;
    pList->head=NULL;
    pList->tail=NULL;
    pList->curr=NULL;
    pList->oobState=2;

    //Make the newly emptied list as current available list
    pList->nextAvailList=currAvailList;
    currAvailList=pList;
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg)
{
    if(pList->size==0)
    {
        return NULL;
    }

    // Despite OOB state or wherever the current pointer is, set it to the head so it can search 
    // and match the target as the current pointer
    pList->curr=pList->head;

    bool match=false;

    //traverse through the list to find the match;
    while(pList->curr!=NULL)
    {
        match=(pComparator)(pList->curr->item, pComparisonArg);

        if(match)
        {
            return pList->curr->item;
        }

        pList->curr=pList->curr->next;
    }

    //If didnt find, mark the out of bond
    pList->oobState=LIST_OOB_END;

    return NULL;
}