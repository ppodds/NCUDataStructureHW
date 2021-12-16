#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *left_child;
    struct Node *right_child;
} Node;

// insert a node with key k into the tree rooted at root
Node *insert(Node *root, int k)
{
    if (root == NULL)
    {
        root = (Node *)malloc(sizeof(Node));
        root->key = k;
        root->left_child = NULL;
        root->right_child = NULL;
    }
    else if (k < root->key)
    {
        root->left_child = insert(root->left_child, k);
    }
    else if (k > root->key)
    {
        root->right_child = insert(root->right_child, k);
    }
    return root;
}

int dfs(Node *root, int count, int target)
{
    if (root == NULL)
        return 0;
    else if ((root->key + count) == target && root->left_child == NULL && root->right_child == NULL)
        return 1;
    else
    {
        if (dfs(root->left_child, count + root->key, target) + dfs(root->right_child, count + root->key, target) >= 1)
            return 1;
        else
            return 0;
    }
}

int main()
{
    int amount;
    scanf("%d", &amount);

    Node *binarySearchTree = NULL;
    for (size_t i = 0; i < amount; i++)
    {
        int key;
        scanf("%d", &key);
        binarySearchTree = insert(binarySearchTree, key);
    }
    int target;
    scanf("%d", &target);
    if (dfs(binarySearchTree, 0, target))
        printf("There exit at least one path in binary search tree.");
    else
        printf("There have no path in binary search tree.");
    return 0;
}