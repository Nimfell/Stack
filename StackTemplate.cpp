#include<stdio.h>

class Stack
{
       class Node
     {
          public:
          int value;
          Node* prev;

          Node(int val=0)
          {
              value = val;
              prev = NULL;
          }
     };
     int stackSize;
     Node* head;

  public:
      Stack()
      {
          head = NULL;
          stackSize = 0;
      }

      int size()
      {
          return stackSize;
      }

      int pop()

      {   if(head != NULL)
          {
               int val = head->value;
               head = head->prev;
               stackSize -= 1;
               return (val);
          }
          return -1;
      }

      void push(int val)
      {
          Node *node = new Node(val);
          if (head == NULL)             
               node -> prev = NULL;
          else
               node -> prev = head;

          head = node;
          stackSize += 1;
      }

      int peek()
      {
          if(head !=NULL)
          {
               int val = head->value;
               return (val);
          }
          return -1;
      }
}; 




