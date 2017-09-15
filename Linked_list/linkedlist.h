#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node{
       int data;
       struct node *next;
       };      

struct node* create_list(int );
struct node* Add_Begin(struct node*, int);
struct node* Remove_Begin(struct node*);

int print_list(struct node* );
int Add_list(struct node*, int);
int Remove_End(struct node*);
int Remove_Position(struct node*, int);
int Add_Position(struct node* head, int pos, int value);
#endif
