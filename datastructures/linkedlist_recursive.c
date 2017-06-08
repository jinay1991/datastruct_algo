#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _node_t_
{
	int value;
	struct _node_t_ *next;
}node_t;
void insert(int value, node_t **head)
{
	if(*head == NULL)
	{
		*head = (node_t*) malloc(sizeof(node_t));
		memset((*head), 0, sizeof(node_t));
		(*head)->value = value;
		(*head)->next = NULL;
	}
	else
	{
		node_t *cur = (*head);
		insert(value, &cur->next);
	}
}
void delete_all(node_t **head)
{
	if(*head == NULL)
		return;
	else
	{
		delete_all(&(*head)->next);
		free((*head));
		*head = NULL;
	}
}

void print_list(node_t *head)
{
	if(head == NULL)
	{
		return;
	}
	else
	{
		print_list(head->next);
		printf("%d ", head->value);
	}
}
int main(int argc, char **argv)
{
	node_t *head = NULL;

	insert(1, &head);
	insert(2, &head);
	insert(3, &head);
	printf("Linked List: ");
	print_list(head);
	printf("\n");

	delete_all(&head);
	printf("Successfully Exited...\n");
	return 0;
}
