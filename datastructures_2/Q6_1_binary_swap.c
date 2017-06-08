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
// swap two Node
void Swap(tree_t **a, tree_t **b)
{
    tree_t *temp = *a;
    *a = *b;
    *b = temp;
}

// A utility function swap left- node & right node of tree
// of every k'th level
void swapEveryKLevelUtil(tree_t *root, int level, int k)
{
    // base case
    if (root == NULL ||
        (root->left == NULL && root->right == NULL))
        return;

    //if current level + 1  is present in swap vector
    //then we swap left & right node
    if ((level + 1) % k == 0)
        Swap(&root->left, &root->right);

    // Recur for left and right subtrees
    swapEveryKLevelUtil(root->left, level + 1, k);
    swapEveryKLevelUtil(root->right, level + 1, k);
}

// This function mainly calls recursive function
// swapEveryKLevelUtil()
void swapEveryKLevel(tree_t *root, int k)
{
    // call swapEveryKLevelUtil function with
    // initial level as 1.
    swapEveryKLevelUtil(root, 1, k);
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

    swapEveryKLevel(root, 2);

    printf("---- Tree in (IN_ORDER) after swap ----\n");
    print_tree(root, IN_ORDER);

    delete_tree(root);
    return 0;
}