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
	struct NODE *curr;

	curr = *head;
	EMPTY_CHECK(curr);
	while(curr != NULL)
	{
		printf("->%d",curr->data);
		curr= curr->next;
	}
	printf("\n");
	return 0;
}

signed char Add_node_beg(struct NODE **head){
	struct NODE *curr;
	curr =(struct NODE *)malloc(sizeof(struct NODE));
	printf("Enter data \n");
	scanf("%d",&curr->data);
	curr->next = *head;
	*head = curr;
	return 0;
}

signed char Add_node_end(struct NODE **head){
	struct NODE *curr;
	curr = *head;
	if(curr == NULL){
		Add_node_beg(head);
		return 0;
	}
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next =(struct NODE *)malloc(sizeof(struct NODE));
	printf("Enter data \n");
	scanf("%d",&curr->next->data);
	curr->next->next = NULL;
	return 0;
}

signed char Insert_at_Position(struct NODE **head){
	struct NODE *curr, *prev;
	unsigned int cnt = 0, pos;
	curr = prev = *head;
	printf("Enter position where you want to insert node\n");
	scanf("%d", &pos);
	if(curr == NULL || cnt == pos){
		Add_node_beg(head);
		return 0;
	}
	while(curr->next != NULL && cnt != pos){
		prev = curr;
		curr = curr->next;
		cnt++;
	}
	prev->next = (struct NODE *)malloc(sizeof(struct NODE));
	printf("Enter data \n");
	scanf("%d",&prev->next->data);
	prev->next->next =curr;
	return 0;
}

signed char Delete_node_frm_end(struct NODE **head){
	struct NODE *curr, *prev;

	curr = prev = *head;
	EMPTY_CHECK(curr);
	while(curr->next != NULL){
		prev = curr;
		curr = curr->next;
	}
	free(prev->next);
	prev->next = NULL;
	return 0;
}

signed char Delete_node_from_begining(struct NODE **head){
	struct NODE *curr;
	curr = *head;

	EMPTY_CHECK(curr);
	curr = curr->next;
	free(*head);
	*head = curr;
	return 0;
}

signed char Delete_node_from_position(struct NODE **head){
	struct NODE *curr, *prev;
	unsigned int cnt = 0, pos;
	curr = prev = *head;
	printf("Enter position where you want to insert node\n");
	scanf("%d", &pos);
	while(curr->next != NULL && cnt != pos){
		prev = curr;
		curr = curr->next;
		cnt++;
	}
	prev->next = curr->next;
	free(curr);
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
signed char Create_circular_list(struct NODE **head){
	struct NODE *curr;
	curr = *head;
	EMPTY_CHECK(curr);
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next = *head;
	return 0;
}
signed char Detect_loop_in_list(struct NODE **head){
	struct NODE *curr, *f_curr;
	unsigned int cnt = 0;
	curr = f_curr = *head;
	EMPTY_CHECK(curr);
	while((curr->next != NULL) && (f_curr->next != NULL)
				&& (f_curr->next->next != NULL)){
		printf("loop count is %d\n", cnt);
		curr = curr->next;
		f_curr = f_curr->next->next;
		if(curr == f_curr){
			printf("List has loop\n");
			return 0;
		}
		cnt++;
	}
	printf("List doesn't have loop\n");
	return 0;
}

int main()
{

	unsigned int c;

	while(1){
		printf("Enter your choise \n"
			"\t 0-> Print nodes \n"
			"\t 1-> Add a node at end \n"
			"\t 2-> Add a node at begining \n"
			"\t 3-> Insert a node at position \n"
			"\t 4-> Delete a node from end \n"
			"\t 5-> Delete a node from begining \n"
			"\t 6-> Delete a node from a position \n"
			"\t 7-> Reverse list \n"
			"\t 8-> Create circular list \n"
			"\t 9-> Detect a loop in list \n");
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
			case 8: Create_circular_list(&Head);
				break;
			case 9: Detect_loop_in_list(&Head);
				break;
			default: return 0;
		}
	}
	return 0;
}
