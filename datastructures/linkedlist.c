#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int value;
    struct list *next;
} list_t;

int insert(int value, struct list **head)
{
    struct list *node_x = (struct list *)malloc(sizeof(struct list));
    node_x->value = value;
    node_x->next = NULL;
    struct list *tail = NULL;
    if (*head == NULL)
    {
        *head = node_x;
        return 0;
    }
    tail = (*head);
    while (tail->next)
    {
        tail = tail->next;
    }
    tail->next = node_x;

    return 0;
}
int delete (int value, struct list **head)
{
    if (!head)
        return 0;
    struct list *current = NULL;
    struct list *prev = NULL;
    current = *head;

    while (current->value != value && current->next != NULL)
    {
        prev = current;
        current = current->next;
    }
    if (current == *head)
        *head = current->next;
    else
    {
        if (current->next)
            prev->next = current->next;
        else
            prev->next = NULL;
    }
    if (current)
    {
        free(current);
        current = NULL;
    }
    return 0;
}
int bubblesort(struct list **head)
{
    struct list *current = NULL;
    current = *head;

    while (current->next)
    {
        struct list *swap[2] = {current, current->next};

        if (swap[0]->value < swap[1]->value)
        {
            struct list *temp = NULL;
            temp = swap[1]->next;
            swap[1]->next = swap[0];
            swap[0]->next = temp;
            // FIXME: handle the head case correctly.
            if (current == *head)
            {
                *head = swap[1];
            }
            current = swap[1];
            continue;
        }
        current = current->next;
    }
    return 0;
}
int print(struct list *head)
{
    struct list *current = NULL;

    current = head;

    while (current)
    {
        printf("Node[%p]: .value: %d, .next: %p\n", current, current->value, current->next);
        current = current->next;
    }
    return 0;
}
int main()
{

    struct list *head = NULL;

    insert(89, &head);
    insert(88, &head);
    insert(90, &head);
    insert(91, &head);
    insert(92, &head);
    insert(93, &head);

    printf("Linked List: \n");
    print(head);

    bubblesort(&head);
    printf("Sorted Linked List:\n");
    print(head);

    printf("Cleaning list...");
    delete (93, &head);
    delete (92, &head);
    delete (91, &head);
    delete (90, &head);
    delete (89, &head);
    delete (88, &head);
    printf("done\n");

    return 0;
}
