#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//#define LINKED_LIST
#define FACTORIAL

#ifdef LINKED_LIST     
 #include "linkedlist.h"
#endif

#ifdef FACTORIAL
 #include "miscell.h"
#endif



          
int main()
{ 
    
  #ifdef LINKED_LIST     
  struct node *Head,*Temp;       
  int value, pos;
  char a;
  
  while(1){
           a = 0;
      printf("\n\n\nChoose option from MENU:\n");  
      printf("1--> Creating node\n");  
      printf("2--> Print list\n");    
      printf("3--> Add a Node at the end\n");   
      printf("4--> Add a Node at the beginning\n"); 
      printf("5--> Remove first Node \n");
      printf("6--> Remove last Node \n");      
      printf("7--> Remove a Node at position\n");            
      printf("8--> Add a Node at position\n");                  
      scanf("%d", &a);       
  
  switch(a)
  {
      case 1:
           printf("Enter a value\n");  
           scanf("%d", &value);
           Head = creat_list(value); 
           Temp = Head; 
           break;         
      case 2:
           Temp = Head;
           printf("List is : ");  
           print_list(Temp);
           
           break;
      case 3:
           Temp = Head;
           printf("Enter a value\n");  
           scanf("%d", &value);
           Add_list(Temp, value);
           break;              
      case 4:
           Temp = Head;
           printf("Enter a value\n");  
           scanf("%d", &value);
           Head = Add_Begin(Temp, value);
           break;           
      case 5:
           Temp = Head;
           Head = Remove_Begin(Temp);
           break;       
      case 6:
           Temp = Head;
           Remove_End(Temp);
           break; 
      case 7:
           Temp = Head;
           printf("Enter a Position\n");  
           scanf("%d", &pos);
           Remove_Position(Temp, pos);
           break; 
      case 8:
           Temp = Head;
           printf("Enter a Position\n");  
           scanf("%d", &pos);
           printf("Enter a Value\n");  
           scanf("%d", &value);
           Add_Position(Temp, pos, value);         
           break;   
           
           
  }
}
   free(Head);
    printf("Linked List END\n");  
 #endif
 
 #ifdef FACTORIAL
 
   int a, i, result;
   
   while(1){
           a = 0;
      printf("\n\n\nChoose option from MENU:\n");  
      printf("1--> Factorial\n");  
      printf("2--> Fibonacci\n");    
            
      scanf("%d", &a);       
      switch(a)
      {
      case 1:         
            printf("Enter the value :");
            scanf("%d",&a);
            result = fact(a);
            printf("\nFact Result = %d\n",result);
      break;
      case 2:
      printf("Enter the value :");
      scanf("%d",&a);            
      printf("\nFibonacci Result : ");                  
      for(i = 0; i < a; i++)
      {
            result = fibonacci(i);
      printf("%d ",result);                              
       }      
      break;
      }
      }
 #endif
 getchar();
 getchar();
  return 0;
}
