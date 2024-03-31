#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <json-c/json.h>
#include <locale.h>
#include <ctype.h>



#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2

/**
 * The list of binary codes in the table
 */
typedef struct stringArray {
	int length;
	char** items;
} stringArray;

// Node structure
typedef struct TreeNode {
	char *str1;
	int		len1;
	char *str2;
	int 	len2;
	struct TreeNode **children;
	int num_children;
	int capacity_children;
} TreeNode;

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	if (size == 0)
		return (strlen(src));
	dst_len = strlen(dst);
	src_len = strlen(src);
	if (size < dst_len + 1)
		return (size + src_len);
	i = 0;
	while (i + dst_len < size - 1 && src[i])
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = 0;
	return (dst_len + src_len);
}

// Function to create a new node
TreeNode* createNode(const char *str1, const char *str2) {
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	node->str1 = strdup(str1);
	node->len1 = strlen(str1);
	node->str2 = strdup(str2);
	node->len2 = strlen(str2);
	node->num_children = 0;
	node->capacity_children = INITIAL_CAPACITY;
	node->children = (TreeNode**)malloc(node->capacity_children * sizeof(TreeNode*));
	if (node->children == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	return node;
}

// Function to add a child to a node
void addChild(TreeNode *parent, TreeNode *child) {
	if (parent->num_children >= parent->capacity_children) {
		parent->capacity_children *= GROWTH_FACTOR;
		parent->children = (TreeNode**)realloc(parent->children, parent->capacity_children * sizeof(TreeNode*));
		if (parent->children == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
	}
	parent->children[parent->num_children] = child;
	parent->num_children++;
}

// Function to print the tree (preorder traversal)
void printTree(TreeNode *root, int depth) {
	if (root == NULL)
		return;
	for (int i = 0; i < depth; i++)
		printf("  ");
	printf("%s\n", root->str1);
	printf("%s\n", root->str2);
	for (int i = 0; i < root->num_children; i++)
		printTree(root->children[i], depth + 1);
}

// Function to free the memory allocated for the tree
void freeTree(TreeNode *root) {
	if (root == NULL)
		return;
	for (int i = 0; i < root->num_children; i++)
		freeTree(root->children[i]);
	free(root->str1);
	free(root->str2);
	free(root->children);
	free(root);
}

int	expand_child(TreeNode *parent, char **chars, int size)
{
	char *prefix;

	if (parent->len1 == parent->len2)
		return (1);
	if (parent->len1 > parent->len2)
		prefix = parent->str1 + parent->len2;
	else
		prefix = parent->str2 + parent->len1;
	int len2 = strlen(prefix);
	for (int i = 0; i < size; i++)
	{
		int len1 = strlen(chars[i]);
		if (!strncmp(chars[i], prefix, len1 < len2 ? len1 : len2))
		{
			char buf[1000];
			buf[0] = 0;

			if (parent->len1 > parent->len2)
				ft_strlcat(buf, parent->str2, 1000);
			else
				ft_strlcat(buf, parent->str1, 1000);
			ft_strlcat(buf, chars[i], 1000);
			if (parent->len1 > parent->len2)
				addChild(parent, createNode(parent->str1, buf));
			else
				addChild(parent, createNode(parent->str2, buf));
		}
	}
	return (0);
}

char *bfs(TreeNode *root, char **chars, int size)
{
	int min_len = 0;
	char	*min_str = NULL;

	TreeNode **queue = (TreeNode**)malloc(100000 * sizeof(TreeNode*));
	if (queue == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	int front = 0, rear = 0;
	queue[rear++] = root;
	for (int i = 0; i < root->num_children; i++)
	{
		queue[rear++] = root->children[i];
	}
	while (front < rear)
	{
		TreeNode *current = queue[front++];
		// 	if (current->len1 > 40)
		// return (strdup("X"));
//		printf("current str1: %s\nstr2:%s\n", current->str1, current->str2);
		if (current->len1 != current->len2)
		{
			if (min_len == 0 || (min_len > 0 && current->len1 < min_len && current->len2 < min_len))
			{
//				printf("expands\n");
				expand_child(current, chars, size);
				for (int i = 0; i < current->num_children; i++)
				{
					queue[rear++] = current->children[i];
				}
			}
		}
		else
		{
			if (min_len == 0 || min_len >= current->len1)
			{
				printf("new res: %s\n", current->str1);
				min_len = current->len1;
				free(min_str);
				min_str = strdup(current->str1);
			}
		}
	}
	free(queue);
	if (!min_str)
		return (strdup("X"));
	return (min_str);
}

char* crashDecode(stringArray codes)
{
	TreeNode *root = createNode("", "");
	char **chars = codes.items;
	int size = codes.length;

	if (size <= 3 && strlen(chars[0]) <= 2 && strlen(chars[1]) <= 2 && strlen(chars[2]) <= 2)
		return (strdup("X"));
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			int len1 = strlen(chars[i]);
			int len2 = strlen(chars[j]);
			if (!strncmp(chars[i], chars[j], len1 < len2 ? len1 : len2))
				addChild(root, createNode(chars[i], chars[j]));
		}
	}
	if (root->num_children == 0)
		return (strdup("X"));
	return bfs(root, chars, size);
}


int main() {
	stringArray codes;
	char *arr[] = {"011100110","011000","0100011","001000","111","0100001101","0000101111","01101100","000001010","011010000","11101010","1000001000","111011","010011","1000011","101010111","1100110011","010100011","010","1000001110"};
	codes.items = arr;
	codes.length = 20;

	printf("%s\n", crashDecode(codes));
	return 0;
}
//111011011000010001000001000
//010011000010111111101010111
//["011100110","011000","0100011","001000","111","0100001101","0000101111","01101100","000001010","011010000","11101010","1000001000","111011","010011","1000011","101010111","1100110011","010100011","010","1000001110"]