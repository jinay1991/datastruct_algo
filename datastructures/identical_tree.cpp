#include <stdio.h>
#include <stdlib.h>
typedef struct _tree_t_
{
	int data;
	struct _tree_t_ *left;
	struct _tree_t_ *right;
}tree_t;

void delete_tree(tree_t *root);
tree_t * insert(int data, tree_t **root);
void print_tree(tree_t *root);

tree_t * insert(int data, tree_t **root)
{
	tree_t *cur = NULL;
	cur = *root;
	if(!cur)
	{
		cur = (tree_t*) malloc(sizeof(tree_t));
		cur->data = data;
		cur->left = NULL;
		cur->right = NULL;
		return cur;
	}
	else
	{
		if (data > cur->data)
			cur->right = insert(data, &cur->right);
		else if (data < cur->data)
			cur->left = insert(data, &cur->left);
		else
			return NULL;
		return cur;
	}
}
void print_tree(tree_t *root)
{
	if (!root)
		return;
	print_tree(root->left);
	printf("%d\n", root->data);
	print_tree(root->right);
}
void delete_tree(tree_t *root)
{
	if (!root)
		return;
	delete_tree(root->left);
	delete_tree(root->right);
	printf("Deleting Node %d\n", root->data);
	free(root);
	root = NULL;
}
int main(int argc, char *argv[])
{
	tree_t *root = NULL;

	insert(10, &root);
	insert(20, &root);
	insert(30, &root);
	printf("-------\n");
	print_tree(root);
	printf("-------\n");
	delete_tree(root);
	print_tree(root);
	return 0;
}
