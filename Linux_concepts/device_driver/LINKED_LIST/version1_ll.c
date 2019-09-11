#include <stdio.h>
#include <stdlib.h>


//printf("%s %d\n", __func__, __LINE__);
#define EMPTY_CHECK(temp) if(temp == NULL ){       \
	               printf("List is empty\n");  \
	               return -1;                  \
	              }                            \

struct NODE{
	int data;
	struct NODE *next;
};

struct NODE *Head = NULL;

signed char Print_nodes(struct NODE **head){
	struct NODE *temp;

	temp = *head;
	EMPTY_CHECK(temp);
	while(temp != NULL)
	{
		printf("->%d",temp->data);
		temp= temp->next;
	}
	printf("\n");
	return 0;
}

signed char Add_node_beg(struct NODE **head){
	struct NODE *temp;
	temp =(struct NODE *)malloc(sizeof(struct NODE));
	printf("Enter data \n");
	scanf("%d",&temp->data);
	temp->next = *head;
	*head = temp;
	return 0;
}

signed char Add_node_end(struct NODE **head){
	struct NODE *temp;
	temp = *head;
	if(temp == NULL){
		Add_node_beg(head);
		return 0;
	}
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next =(struct NODE *)malloc(sizeof(struct NODE));
	printf("Enter data \n");
	scanf("%d",&temp->next->data);
	temp->next->next = NULL;
	return 0;
}

signed char Insert_at_Position(struct NODE **head){
	struct NODE *temp, *prev;
	unsigned int cnt = 0, pos;
	temp = prev = *head;
	printf("Enter position where you want to insert node\n");
	scanf("%d", &pos);
	if(temp == NULL || cnt == pos){
		Add_node_beg(head);
		return 0;
	}
	while(temp->next != NULL && cnt != pos){
		prev = temp;
		temp = temp->next;
		cnt++;
	}
	prev->next = (struct NODE *)malloc(sizeof(struct NODE));
	printf("Enter data \n");
	scanf("%d",&prev->next->data);
	prev->next->next =temp;
	return 0;
}

signed char Delete_node_frm_end(struct NODE **head){
	struct NODE *temp, *prev;

	temp = prev = *head;
	EMPTY_CHECK(temp);
	while(temp->next != NULL){
		prev = temp;
		temp = temp->next;
	}
	free(prev->next);
	prev->next = NULL;
	return 0;
}

signed char Delete_node_from_begining(struct NODE **head){
	struct NODE *temp;
	temp = *head;

	EMPTY_CHECK(temp);
	temp = temp->next;
	free(*head);
	*head = temp;
	return 0;
}

signed char Delete_node_from_position(struct NODE **head){
	struct NODE *temp, *prev;
	unsigned int cnt = 0, pos;
	temp = prev = *head;
	printf("Enter position where you want to insert node\n");
	scanf("%d", &pos);
	while(temp->next != NULL && cnt != pos){
		prev = temp;
		temp = temp->next;
		cnt++;
	}
	prev->next = temp->next;
	free(temp);
	if(cnt == 0){
		*head = prev->next;
	}
	return 0;
}

signed char Reverse_list(struct NODE **head){
	 struct NODE *curr, *prev, *next;
	 curr = *head;
	 prev = next = NULL;

	 EMPTY_CHECK(curr);
	 while(curr->next != NULL){
	 	 next = curr->next;
	 	 curr->next = prev;
	 	 prev = curr;
	 	 curr = next;
	 }
	 curr->next = prev;
	 *head = curr;
	 return 0;
}
int main()
{

	unsigned int c;

	while(1){
		printf("Enter your choise \n");
		printf("\t 0-> Print nodes \n");
		printf("\t 1-> Add a node at end \n");
		printf("\t 2-> Add a node at begining \n");
		printf("\t 3-> Insert a node at position \n");
		printf("\t 4-> Delete a node from end \n");
		printf("\t 5-> Delete a node from begining \n");
		printf("\t 6-> Delete a node from a position \n");
		printf("\t 7-> Reverse list \n");
		scanf("%d",&c);

		switch(c){

			case 0: Print_nodes(&Head);
				break;
			case 1: Add_node_end(&Head);
				break;
			case 2: Add_node_beg(&Head);
				break;
			case 3: Insert_at_Position(&Head);
				break;
			case 4: Delete_node_frm_end(&Head);
				break;
			case 5: Delete_node_from_begining(&Head);
				break;
			case 6: Delete_node_from_position(&Head);
				break;
			case 7: Reverse_list(&Head);
				break;
			default: return 0;
		}
	}
	return 0;
}
