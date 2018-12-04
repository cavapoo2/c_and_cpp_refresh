#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void insertFront(Node **head, int data);
void insertBack(Node *head, int data);
void printNodes(Node *head);

void insertBack(Node *head, int data)
{
    //allocate new Node
    Node *new_node = (Node *)calloc(1, sizeof(Node));
    new_node->data = data;
    if (head != NULL)
    {
        //find end of nodes
        Node *cur = head;
        Node *prev = head;
        while (cur != NULL)
        {
            prev = cur;
            cur = cur->next;
        }
        prev->next = new_node;
    }
    else
    {
        head = new_node;
    }
}
void insertFront(Node **head, int data)
{
    Node *new_node = (Node *)calloc(1, sizeof(Node));
    if (new_node)
    {
        new_node->data = data;
        new_node->next = *head;
        *head = new_node;
    }
    else {
        printf("Error allocating memory for insertFront\n");
    }
}
void printNodes(Node *head)
{
    Node *start = head;
    printf("In:\n");
    while (start != NULL)
    {
        printf("%d,", start->data);
        start = start->next;
    }
    printf("\n");
}
void printNodesMsg(Node *head,const char* msg)
{
    Node *start = head;
    printf("%s\n",msg);
    printf("In:\n");
    while (start != NULL)
    {
        printf("%d,", start->data);
        start = start->next;
    }
    printf("\n");
}

void clearNodes(Node **head)
{
    Node *cur = *head;
    while (cur != NULL)
    {
        Node *nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    *head = NULL;
}
void reverse(Node** head) {
    if(*head == NULL) {
        return;
    } 
    Node* cur = *head;
    Node* prev = NULL;
    while(cur) {
        Node* nxt = cur->next;
        if(nxt == NULL){
            *head = cur;
        }
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
}
Node* testReverse(Node* in) {
    reverse(&in);
    return in;
}
Node* generateN(int n) {
    Node *head = (Node*) calloc(1,sizeof(Node));
    for(int i=1; i < n; i++){
        insertBack(head,i);
    }
    return head;
}

int main(void)
{
    Node *head = (Node *)calloc(1, sizeof(Node));
    for (int i = 1; i < 10; i++)
    {
        insertBack(head, i);
    }
    //now print
    printNodes(head);
    clearNodes(&head);
    printNodes(head);

    head = (Node *)calloc(1, sizeof(Node));
    for (int i = 1; i < 10; i++)
    {
        insertFront(&head, i);
    }
    printNodes(head);
    clearNodes(&head);
    printNodes(head);
    //try reverse
    head = generateN(10);
    printNodesMsg(head,"before reverse");
    reverse(&head);
    printNodesMsg(head,"after reverse");
    return 0;
}