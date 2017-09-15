#include <stdio.h>
#include "linkedlist.h"

int print_list(struct node* ptr)
{     
      while(ptr!=NULL){
      printf("%d  ",ptr->data);
      ptr = ptr->next;
      }
      return 0;
}

struct node* creat_list(int value)
{
  struct node* ptr;
      ptr = (struct node*)malloc(sizeof(struct node));
      if(ptr == NULL)
       printf("\nCreation failed");
      ptr->data = value;
      ptr->next = NULL;
 return ptr;
}

int Add_list(struct node* head, int value)
{
  struct node* temp;
      
      while(head->next != NULL)
        head = head->next;
      temp = (struct node*)malloc(sizeof(struct node));
      if(temp == NULL)
       printf("\nCreation failed");
      temp->data = value;
      temp->next = NULL;
      head->next = temp;
      return 0;
}

struct node* Add_Begin(struct node* head, int value)
{
   struct node* temp;
   
   temp = (struct node*)malloc(sizeof(struct node));
   if(temp == NULL)
       printf("\nCreation failed");
   temp->next = head;
   temp->data = value;
   return temp;
  
}

struct node* Remove_Begin(struct node* head)
{   
    struct node* temp = head->next;
     free(head);
     return temp;
}
int Remove_End(struct node* head)
{
     while(head->next->next != NULL)
           head = head->next;
     head->next = NULL; 
     return 0;    
}

int Add_Position(struct node* head, int pos, int value)
{
  int cnt = 1;
  struct node* temp;
 
  temp = (struct node*)malloc(sizeof(struct node));
  while((head->next != NULL) && cnt != (pos-1))
     {
             head = head->next;
             cnt++;
      }
  if(head->next == NULL)
  {
    printf("\nWrong Position");
    return -1;
  }
                
  temp->data = value;
  temp->next = head->next;
  head->next = temp;
        return 0;
}

int Remove_Position(struct node* head, int pos)
{
  int cnt = 1;
  struct node* temp = head;
  if(pos == 1)
    {
         printf("\nUse another opttion to delete 1st postion");            
        return -1;
    }
  while((cnt != (pos-1)))
  {
        temp= temp->next;
        cnt++;
  }
  if(temp->next == NULL)
    {
      printf("\nWrong Position");
      return -1;
    }
  temp->next = temp->next->next; 
  return 0;       
}
