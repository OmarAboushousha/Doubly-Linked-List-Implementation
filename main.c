#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct
{
    Node* head;
    Node* tail;
} DoublyLinkedList;

DoublyLinkedList* init()
{
    DoublyLinkedList *list =malloc(sizeof(DoublyLinkedList));
    list->head=NULL;
    list->tail=NULL;
    return list;
}

int isEmpty(DoublyLinkedList* list)
{
    if(list->head == NULL)
        return 1;
    else
        return 0;
}

Node* newNode(int value)
{
    Node* node = malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

DoublyLinkedList* convertArrayToDoublyLinkedList(int array[], int size)
{
    DoublyLinkedList *list = init();

    for(int i = 0; i < size; i++)
    {
        Node* node = newNode(array[i]);

        if(isEmpty(list))
            list->head = list->tail = node;
        else
        {
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
        }
    }
    return list;
}

void destroy(DoublyLinkedList* list)
{
    Node* temp;
    while(list->head != NULL)
    {
        temp = list->head;
        list->head = temp->next;
        temp = NULL;
    }
    list->head = NULL;
    list->tail = NULL;
}

DoublyLinkedList* copy(DoublyLinkedList* list)
{
    DoublyLinkedList *newlist = init();
    Node* temp;
    Node* store = list->head;
    while(list->head != NULL)
    {
        temp = list->head;
        list->head = temp->next;
        if(isEmpty(newlist))
            newlist->head = newlist->tail = temp;
        else
        {
            newlist->tail->next = temp;
            temp->prev = newlist->tail;
            newlist->tail = temp;
        }
    }
    list->head = store;
    return newlist;
}

size_t length(DoublyLinkedList*  list)
{
    size_t count = 0;
    DoublyLinkedList* listCopy = copy(list);
    Node* temp;
    while(listCopy->head != NULL)
    {
        temp = listCopy->head;
        listCopy->head = temp->next;
        count++;
    }
    return count;
}

void concatenate(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    if(isEmpty(list1))
    {
        list1->head = list2->head;
        list1->tail = list2->tail;
    }
    else if(!isEmpty(list1) && !isEmpty(list2))
    {
        list1->tail->next = list2->head;
        list1->tail = list2->tail;
        list2->head = list1->head;
    }
}

DoublyLinkedList* getDifferenceBetweenLists(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    DoublyLinkedList *newlist = init();
    DoublyLinkedList* listCopy1 = copy(list1);
    DoublyLinkedList* listCopy2 = copy(list2);
    Node* temp;
    int differences[10];
    int i = 0, size = 0;
    while(listCopy1->head != NULL)
    {
        while(listCopy2->head != NULL)
        {
            if(listCopy1->head->data == listCopy2->head->data)
                break;
            else
            {
                temp = listCopy2->head;
                listCopy2->head = temp->next;
            }
        }
        if(listCopy2->head == NULL)
        {
            size++;
            differences[i] = listCopy1->head->data;
            i++;
        }
        listCopy2 = copy(list2);
        temp = listCopy1->head;
        listCopy1->head = temp->next;
    }
    newlist = convertArrayToDoublyLinkedList(differences, size);
    return newlist;
}

int checkSumofFirstHalfEqualSumOfSecondHalf(DoublyLinkedList*  list)
{
    DoublyLinkedList* listCopy = copy(list);
    int sum1 = 0, sum2 = 0;
    Node* tempForward;
    Node* tempBackward;
    if(length(listCopy) % 2 != 0)
        return 0;
    else
    {
        while(listCopy->head->prev != listCopy->tail)
        {
            tempForward = listCopy->head;
            listCopy->head = tempForward->next;
            sum1 += tempForward->data;
            tempBackward = listCopy->tail;
            listCopy->tail = tempBackward->prev;
            sum2 += tempBackward->data;
        }
        if(sum1 == sum2)
            return 1;
        else
            return 0;
    }
}

int isPalindrome(DoublyLinkedList * list)
{
    DoublyLinkedList* listCopy = copy(list);
    Node* tempForward;
    Node* tempBackward;
    if(isEmpty(listCopy) || (length(listCopy) == 1))
        return 1;
    else
    {
        if((length(listCopy) % 2) == 0)
        {
            while(listCopy->head->prev != listCopy->tail)
            {
                if(listCopy->head->data != listCopy->tail->data)
                    return 0;
                else
                {
                    tempForward = listCopy->head;
                    listCopy->head = tempForward->next;
                    tempBackward = listCopy->tail;
                    listCopy->tail = tempBackward->prev;
                }
            }
        }
        else
        {
            while(listCopy->head != listCopy->tail)
            {
                if(listCopy->head->data != listCopy->tail->data)
                    return 0;
                else
                {
                    tempForward = listCopy->head;
                    listCopy->head = tempForward->next;
                    tempBackward = listCopy->tail;
                    listCopy->tail = tempBackward->prev;
                }
            }
        }
    }
    return 1;
}

int areEqual(DoublyLinkedList*  list1, DoublyLinkedList*  list2)
{
    DoublyLinkedList* listCopy1 = copy(list1);
    DoublyLinkedList* listCopy2 = copy(list2);
    Node* temp;
    if(length(listCopy1) != length(listCopy2))
        return 0;
    else
    {
        while(listCopy1->head != NULL)
        {
            if(listCopy1->head->data != listCopy2->head->data)
                return 0;
            else
            {
                temp = listCopy1->head;
                listCopy1->head = temp->next;
                temp = listCopy2->head;
                listCopy2->head = temp->next;
            }
        }
    }
    return 1;
}

void printlnListForward(DoublyLinkedList * list)
{
    if(isEmpty(list))
        printf(" ");
    else
    {
        DoublyLinkedList* listCopy = copy(list);
        Node* temp = listCopy->head;
        listCopy->head = temp->next;
        printf("%d", temp->data);
        while(listCopy->head != NULL)
        {
            temp = listCopy->head;
            listCopy->head = temp->next;
            printf(" %d", temp->data);
        }
    }
    printf("\n");
}

void printlnListBackward(DoublyLinkedList * list)
{
    if(isEmpty(list))
        printf(" ");
    else
    {
        DoublyLinkedList* listCopy = copy(list);
        Node* temp = listCopy->tail;
        listCopy->tail = temp->prev;
        printf("%d", temp->data);
        while(listCopy->tail != NULL)
        {
            temp = listCopy->tail;
            listCopy->tail = temp->prev;
            printf(" %d", temp->data);
        }
    }
    printf("\n");
}

void Investigate(char* title, DoublyLinkedList * list)
{
    printf("%s\n", title);
    printf("List =         ");
    printlnListForward(list);
    printf("Reverse List = ");
    printlnListBackward(list);
    printf("List Length = %u\n", length(list));
    printf("List isPalindrome = %d\n", isPalindrome(list));
    printf("...................................................\n");
}

void testConcatenate1(DoublyLinkedList *list1)
{
    puts("\nSTART testConcatenate1\n");
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList* list3,*emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", EmptyList);
    concatenate(list3, emptyList1);
    Investigate("List3<->EmptyList1\n==========================", list3);
    destroy(list3);
    Investigate("List3 (after destroy)\n=====================", list3);
    destroy(emptyList1);
    puts("\nEND testConcatenate1\n");
}

void testConcatenate2(DoublyLinkedList * list1)
{
    puts("\nSTART testConcatenate2\n");
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList * list3, * emptyList1;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", EmptyList);
    concatenate(emptyList1, list3);
    Investigate("EmptyList1<->List3\n==========================", emptyList1);
    destroy(emptyList1);
    Investigate("EmptyList1 (after destroy)\n=====================", emptyList1);
    puts("\nEND testConcatenate2\n");

}

void testConcatenate3(DoublyLinkedList *list1, DoublyLinkedList *list2)
{
    puts("\nSTART testConcatenate3\n");
    DoublyLinkedList* list3, *list4;
    list3 = copy(list1);
    Investigate("List3 = copy(List1)\n==================", list3);
    list4 = copy(list2);
    Investigate("list4 = copy(List2)\n==================", list4);
    concatenate(list3, list4);
    Investigate("List3<->List4\n=====================", list3);
    destroy(list3);
    Investigate("list3 (after destroy)\n=====================", list3);
    puts("\nEND testConcatenate3\n");

}

void testConcatenate()
{
    int array1[] = {0, 1, 2, 3, 4, 5, 6};
    int array2[] = {7, 8, 9};

    DoublyLinkedList *list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
    Investigate("List1\n=====", list1);
    DoublyLinkedList *list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
    Investigate("List2\n=====", list2);

    testConcatenate1(list1);
    testConcatenate2(list1);
    testConcatenate3(list1, list2);

    destroy(list1);
    destroy(list2);
}

void testPalindrome()
{
    puts("\nSTART testPalindrome\n");
    int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array4[] = {7, 8, 9, 9, 8, 7};

    DoublyLinkedList* list5 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
    Investigate("List5\n=====", list5);
    DoublyLinkedList *list6 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
    Investigate("List6\n=====", list6);

    destroy(list5);
    destroy(list6);
    puts("\nEND testPalindrome\n");

}

void testAreEqual()
{
    puts("\nSTART testAreEqual\n");
    int array7[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array8[] = {7, 8, 9, 9, 8, 7};
    int array9[] = {0, 1, 2, 3, 4, 5};
    DoublyLinkedList * EmptyList =init();
    DoublyLinkedList *list7 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("List7\n=====", list7);
    DoublyLinkedList *list8 = convertArrayToDoublyLinkedList(array8, sizeof(array8)/sizeof(*array8));
    Investigate("List8\n=====", list8);
    DoublyLinkedList *list9 = convertArrayToDoublyLinkedList(array9, sizeof(array9)/sizeof(*array9));
    Investigate("List9\n=====", list9);
    DoublyLinkedList *emptyList1 = copy(EmptyList);
    Investigate("EmptyList1 = copy(EmptyList)\n===========================", emptyList1);
    DoublyLinkedList *emptyList2 = copy(EmptyList);
    Investigate("EmptyList2 = copy(EmptyList)\n===========================", emptyList2);

    printf("areEqual(list7, list7) = %d\n", areEqual(list7, list7));
    printf("areEqual(list7, list8) = %d\n", areEqual(list7, list8));
    printf("areEqual(list7, list9) = %d\n", areEqual(list7, list9));
    printf("areEqual(list8, list7) = %d\n", areEqual(list8, list7));
    printf("areEqual(list7, EmptyList1) = %d\n", areEqual(list7, emptyList1));
    printf("areEqual(EmptyList1, list7) = %d\n", areEqual(emptyList1, list7));
    printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

    destroy(list7);
    destroy(list8);
    destroy(list9);
    puts("\nEND testAreEqual\n");

}

void testDifference()
{
    puts("\nSTART testDifference\n");
    int array10[] = {2, 4, 8, 9, 13, 17,20};
    int array11[] = {2, 8, 17,20};
    DoublyLinkedList *list10 = convertArrayToDoublyLinkedList(array10, sizeof(array10)/sizeof(*array10));
    Investigate("list10\n=====", list10);
    DoublyLinkedList *list11 =convertArrayToDoublyLinkedList(array11, sizeof(array11)/sizeof(*array11));
    Investigate("List11\n=====", list11);
    DoublyLinkedList *list12 = getDifferenceBetweenLists(list10,list11);
    Investigate("list12\n=====", list12);
    destroy(list10);
    destroy(list11);
    destroy(list12);
    puts("\nEND testDifference\n");

}
void testSum()
{
    puts("\nSTART testSum\n");
    int array5[] = {12, 4, 8, 9, 13, 2};
    int array6[] = {2, 18, 17,4};
    int array7[]= {2,3,4};
    DoublyLinkedList *list13 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
    Investigate("list13\n=====", list13);
    DoublyLinkedList *list14 =convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
    Investigate("list14\n=====", list14);
    DoublyLinkedList *list15 =convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("list15\n=====", list15);
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list13) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list13));
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list14) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list14));
    printf("checkSumofFirstHalfEqualSumOfSecondHalf(list15) = %d\n", checkSumofFirstHalfEqualSumOfSecondHalf(list15));

    destroy(list13);
    destroy(list14);
    destroy(list15);
    puts("\nEND testSum\n");
}
int main()
{
    testConcatenate();
    testPalindrome();
    testAreEqual();
    testDifference();
    testSum();
    return 0;
}
