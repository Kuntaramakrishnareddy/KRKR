#include<stdio.h>
#include<stdlib.h>

struct NODE{
        struct NODE *l_link;
        int data;
        struct NODE *r_link;
};
struct NODE *Head = NULL;

inline void allocate_mem(struct NODE **tp)
{
        *tp = (struct NODE *) malloc(sizeof(struct NODE));
        printf("\nEnter the data");
        scanf("%d", &((*tp)->data));
}

int create_list(struct NODE **np)
{
        struct NODE *temp, *lp;
        int n = 0 ;

        lp = *np;
        printf("Enter number of nodes to create");
        scanf("%d", &n);
        while(n > 0){
                if(lp == NULL)
                {
                        allocate_mem(&lp);
                        lp->r_link = NULL;
                        lp->l_link = NULL;
                        Head = lp;
                }
                while(lp->r_link != NULL)
                        lp=lp->r_link;
                allocate_mem(&temp);
                lp->r_link = temp;
                temp->r_link = NULL;
                temp->l_link = lp;
                n--;
        }

        return 0;
}

/* recursive */
int print_list(struct NODE **np)
{
        struct NODE *temp;

        temp = *np;
        if(temp == NULL) return 0;
        printf("\n%d", temp->data);
        temp = temp->r_link;
        print_list(&temp);
}
#if 0
int print_list(struct NODE **np)
{
        struct NODE *temp;

        temp = *np;
        while(temp != NULL)
        {
                printf("\n%d", temp->data);
                temp = temp->r_link;
        }
}
#endif

int push(struct NODE **np)
{
        struct NODE *temp = NULL;

        allocate_mem(&temp);
        (*np)->l_link = temp;
        temp->r_link = *np;
        *np = temp;
}

int pop(struct NODE **np)
{
        struct NODE *temp = NULL;
        temp = *np;
        *np = temp->r_link;
        free(temp);
}

void NumOfNodes(struct NODE **tp)
{
        static unsigned int TCounter = 0;
        struct NODE *temp = NULL;
        if(*tp == NULL)
        {
                printf("\nNumber of nodes are %d",TCounter);
                TCounter = 0;
                return ;
        }
        temp = *tp;
        temp = temp->r_link;
        TCounter++;
        NumOfNodes(&temp);
}

int main(int argc, char **argv)
{
        int option=0;

        while(1)
        {
        printf("\nEnter your choice of operations");
        printf("\n\t 0. Exit");
        printf("\n\t 1. Create list");
        printf("\n\t 2. Printf list");
        printf("\n\t 3. push to list");
        printf("\n\t 4. pop from list");
        printf("\n\t 5. Number of node in list");
        scanf("%d", &option);

        switch(option)
        {

                case 1: create_list(&Head);
                        break;
                case 2: print_list(&Head);
                        break;
                case 3: push(&Head);
                        break;
                case 4: pop(&Head);
                        break;
                case 5: NumOfNodes(&Head);
                        break;
                case 0:
                        exit(0);
        }
        }
        return 0;

