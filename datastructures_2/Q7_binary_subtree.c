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

#define true  (1)
#define false (0)
typedef unsigned char bool;

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
/* utility function */
bool areIdentical(tree_t *root1, tree_t *root2)
{
    /* base cases */
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    /* Check if the data of both roots is same and data of left and right
       subtrees are also same */
    return (root1->value == root2->value &&
            areIdentical(root1->left, root2->left) &&
            areIdentical(root1->right, root2->right));
}

/* This function returns true if S is a subtree of T, otherwise false */
bool isSubtree(tree_t *T, tree_t *S)
{
    /* base cases */
    if (S == NULL)
        return true;

    if (T == NULL)
        return false;

    /* Check the tree with root as current node */
    if (areIdentical(T, S))
        return true;

    /* If the tree with root as current node doesn't match then
       try left and right subtrees one by one */
    return isSubtree(T->left, S) ||
           isSubtree(T->right, S);
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
    tree_t *T = NULL;

    T = insert(T, 3);
    insert(T, 3);
    insert(T, 10);
    insert(T, 6);
    insert(T, 4);
    insert(T, 30);
    printf("---- Tree T in (IN_ORDER) ----\n");
    print_tree(T, IN_ORDER);

    tree_t *S = NULL;
    S = insert(S, 10);
    insert(S, 6);
    insert(S, 4);
    insert(S, 30);
    printf("---- Tree S in (IN_ORDER) ----\n");
    print_tree(S, IN_ORDER);

    if (isSubtree(T, S))
        printf("Tree 2 is subtree of Tree 1\n");
    else
        printf("Tree 2 is not a subtree of Tree 1\n");

    delete_tree(T);
    delete_tree(S);
    return 0;
}