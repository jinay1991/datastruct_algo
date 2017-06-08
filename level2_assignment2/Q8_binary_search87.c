#include <stdio.h>
#include <stdlib.h>

typedef struct _tree_t_
{
    struct _tree_t_ *left;
    struct _tree_t_ *right;
    int value;
} tree_t;
typedef enum _traversal_t_ {
    IN_ORDER,   // Left - Root - Right
    PRE_ORDER,  // Root - Left - Right
    POST_ORDER // Left - Right - Root
} traversal_t;
////////////////// --------- Helper Functions --------- //////////////////
static tree_t *createNode(int value)
{
    tree_t *new_node = (tree_t *)malloc(sizeof(tree_t));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
tree_t *insert(tree_t *root, int value)
{
    if (!root)
        return createNode(value);

    tree_t *node = (tree_t *)root;
    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return NULL;

    return node;
}
void delete_tree(tree_t *root)
{
    if (!root)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    printf("Deleting node %d\n", root->value);
    free(root);
    root = NULL;
}
tree_t *search(tree_t *root, int value)
{
    if (!root || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);
    else if (value > root->value)
        return search(root->right, value);
    else
        return NULL;
}
void print_tree(tree_t *root, traversal_t traverse_method)
{
    if (!root)
        return;

    switch (traverse_method)
    {
    case IN_ORDER:
    {
        print_tree(root->left, IN_ORDER);
        printf("%d \n", root->value);
        print_tree(root->right, IN_ORDER);
        break;
    }
    case PRE_ORDER:
    {
        printf("%d \n", root->value);
        print_tree(root->left, PRE_ORDER);
        print_tree(root->right, PRE_ORDER);
        break;
    }
    case POST_ORDER:
    {
        print_tree(root->left, POST_ORDER);
        print_tree(root->right, POST_ORDER);
        printf("%d \n", root->value);
        break;
    }
    default:
    {
        printf("Invalid traverse_method\n");
        break;
    }
    }
}
int main(int argc, char *argv[])
{
    tree_t *root = NULL;
    // 22,11,07,84,55,78,67,66,89,90
    root = insert(root, 22);
    insert(root, 11);
    insert(root, 7);
    insert(root, 84);
    insert(root, 55);
    insert(root, 78);
    insert(root, 67);
    insert(root, 66);
    insert(root, 89);
    insert(root, 90);
    printf("---- Tree in (IN_ORDER) ----\n");
    print_tree(root, IN_ORDER);

    tree_t *query = search(root, 84);
    printf("query node for value 84: \n{.left:%p, .right: %p, .root: %p, .value: %d }\n", query->left, query->right, query, query->value);

    delete_tree(root);
    return 0;
}