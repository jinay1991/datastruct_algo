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
int findMin(tree_t *node)
{
    tree_t *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }
    return (current->value);
}
// Returns maximum value in a given Binary Tree
int findMax(tree_t *root)
{
    // Base case
    if (root == NULL)
        return -1;

    // Return maximum of 3 values:
    // 1) Root's data 2) Max in Left Subtree
    // 3) Max in right subtree
    int res = root->value;
    int lres = findMax(root->left);
    int rres = findMax(root->right);
    if (lres > res)
        res = lres;
    if (rres > res)
        res = rres;
    return res;
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

    root = insert(root, 20);
    insert(root, 10);
    insert(root, 30);
    insert(root, 40);
    insert(root, 50);
    insert(root, 60);
    printf("---- Tree in (IN_ORDER) ----\n");
    print_tree(root, IN_ORDER);

    int min_value = findMin(root);
    printf("min value in the list: %d\n",min_value);

    int max_value = findMax(root);
    printf("max value in the list: %d\n",max_value);
    delete_tree(root);
    return 0;
}