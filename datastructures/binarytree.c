/* 
 * Complete Binary Search Tree Implementation asked on Amazon Kindle SDE II Interview 
 * Reference: www.geeksforgeeks.org
 * Created by Jinay Patel
 */

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
    POST_ORDER, // Left - Right - Root
    LEVEL_ORDER
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
static tree_t *minValNode(tree_t *node)
{
    tree_t *current = node;
    while (!current->left)
        current = current->left;
    return current;
}
/////////////////////////////////////////////////////////////////////////

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
tree_t *delete (tree_t *root, int value)
{
    if (!root)
        return root;
    if (value == root->value)
    {
        if (root->left || root->right)
        {
            printf("Note: Deletion of Root Node before deleting Childs is not allowed.\n");
            return root;
        }
        else
        {
            if (root)
            {
                free(root);
                root = NULL;
            }
            return root;
        }
    }

    if (value < root->value)
        root->left = delete (root->left, value);
    else if (value > root->value)
        root->right = delete (root->right, value);
    else
    {
        if (!root->left)
        {
            tree_t *temp = root->right;
            free(root);
            root = NULL;
            return temp;
        }
        else if (!root->right)
        {
            tree_t *temp = root->left;
            free(root);
            root = NULL;
            return temp;
        }

        tree_t *temp = minValNode(root->right);
        root->value = temp->value;
        root->right = delete (root->right, temp->value);
    }
    return root;
}
int getMaxLevel(tree_t *root)
{
    if (!root)
        return 0;

    int leftLevel = getMaxLevel(root->left);
    int rightLevel = getMaxLevel(root->right);

    if (leftLevel > rightLevel)
        return leftLevel + 1;
    return rightLevel + 1;
}
void levelOrderUtil(tree_t *root, int level)
{
    if (!root)
        return;
    if (level == 1)
        printf("%d \n", root->value);
    else
    {
        levelOrderUtil(root->left, level - 1);
        levelOrderUtil(root->right, level - 1);
    }
}
void leftProjectionUtil(tree_t *root, int level, int *max_level)
{
    if (!root)
        return;

    if (*max_level < level)
    {
        printf("%d \n", root->value);
        *max_level = level;
    }

    leftProjectionUtil(root->left, level + 1, max_level);
    leftProjectionUtil(root->right, level + 1, max_level);
}
void leftProjection(tree_t *root)
{
    int max_level = 0;
    leftProjectionUtil(root, 1, &max_level);
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
        case LEVEL_ORDER:
        {
            int level = 0;
            int maxLevel = getMaxLevel(root);
            for (level = 1; level <= maxLevel; level++)
                levelOrderUtil(root, level);
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
    printf("---- Tree in (PRE_ORDER) ----\n");
    print_tree(root, PRE_ORDER);
    printf("---- Tree in (POST_ORDER) ----\n");
    print_tree(root, POST_ORDER);
    printf("---- Tree in (LEVEL_ORDER) ----\n");
    print_tree(root, LEVEL_ORDER);

    tree_t *query = search(root, 30);
    printf("query node for value 30: {.left:%p, .right: %p, .root: %p, .value: %d }\n", query->left, query->right, query, query->value);

    printf("--- Left Projection --- \n");
    leftProjection(root);

    delete (root, 60);
    delete (root, 50);
    delete (root, 40);
    delete (root, 30);
    delete (root, 10);
    delete (root, 20);
    printf("---- After Deletion ----\n");
    print_tree(root, IN_ORDER);

    return 0;
}