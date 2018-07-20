#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct _node_s {
    struct _node_s* left;
    struct _node_s* right;
    void* val;
} node_t;

typedef int (*cmp_handler_t)(void* a, void* b);

typedef struct _tree_s {
    node_t* root;
    cmp_handler_t cmp;
}tree_t;

tree_t* create_tree(cmp_handler_t handler) {
    tree_t* ret = malloc(sizeof(tree_t));
    if (NULL == ret) {
        return NULL;
    }

    ret->root = NULL;
    ret->cmp = handler;

    return ret;
}

void destory(node_t* node) {
    if (node) {
        if (node->left) {
            destory(node->left);
        }

        if (node->right) {
            destory(node->right);
        }
        free(node);
    }
}

void destory_tree(tree_t *tree) {
    if (NULL == tree) {
        return ;
    }
    destory(tree->root);    
}

void insert(cmp_handler_t handler, node_t* root, node_t* val) {
    if (NULL == root) {
        return ;
    }

    if (handler(root->val, val->val) < 0) {
        if (NULL == root->left) {
            root->left = val;
        } else {
            insert(handler, root->left, val);
        }
    } else {
        if (NULL == root->right) {
            root->right = val;
        } else {
            insert(handler, root->right, val);
        }
    }
}

void insert_tree(tree_t* tree, void* val) {
    if (NULL == tree) {
        return ;
    }

    node_t* n = malloc(sizeof(node_t));
    n->left = NULL;
    n->right = NULL;
    n->val = val;

    node_t *root = tree->root;
    if (NULL == root) {
        tree->root = n;
    } else {
        insert(tree->cmp, root, n);
    }
}

int handler(void* a, void* b) {
    int* x = (int*)a;
    int* y = (int*)b;

    return (*x) - (*y);
}

int main(int argc, char** argv) {
    tree_t* tree = create_tree(handler);
    int arr[] = {3, 2, 4, 1, 5};
    insert_tree(tree, arr);
    insert_tree(tree, arr+1);
    insert_tree(tree, arr+2);
    insert_tree(tree, arr+3);
    insert_tree(tree, arr+4);

    return 0;
}
