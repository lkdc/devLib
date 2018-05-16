#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef struct bst_node bst_node_t;
struct bst_node{
    bst_node_t *left;
    bst_node_t *right;
    int data;
};

bst_node_t *new_node(int data);
void insert_node(bst_node_t **root, int data);
void delete_node(bst_node_t **root, int data);
bst_node_t *min_node(bst_node_t *root);
bst_node_t *max_node(bst_node_t *root);
bst_node_t *successor(bst_node_t *root, bst_node_t *node);
bst_node_t *predecessor(bst_node_t *root, bst_node_t *node);
bst_node_t *find(bst_node_t *root, int data);
void inorder(bst_node_t *root);
void preorder(bst_node_t *root);
void postorder(bst_node_t *root);

bst_node_t *new_node(int data)
{
    bst_node_t *p;
    p = (bst_node_t*)malloc(sizeof(bst_node_t));
    assert(p != NULL);
    p->left = NULL;
    p->right = NULL;
    p->data = data;
    return p;
}

void insert_node(bst_node_t **root, int data)
{
    bst_node_t **p = root;

    while (*p != NULL){
        if (data < (*p)->data){
            p = &(*p)->left;
        } else if(data > (*p)->data){
            p = &(*p)->right;
        } else return;
    }
    *p = new_node(data);
}

void delete_node(bst_node_t **root, int data)
{
    bst_node_t **p = root;
    bst_node_t *p_free = NULL;
    bst_node_t *p_min = NULL;

    if(!p){
        return;
    } else {
        while (*p != NULL){
            if (data < (*p)->data){
                p = &(*p)->left;
            } else if(data > (*p)->data){
                p = &(*p)->right;
            } else break;
        }
    }
    if(!(*p)){
        printf("Node not found\n");
        return;
    }
    if ((*p)->right == NULL){
        p_free = *p;
        *p = (*p)->left;
        free(p_free);
    } else{
        p_min = min_node((*p)->right);
        (*p)->data = p_min->data;
        delete_node(&(*p)->right, p_min->data);
    }
}

bst_node_t *min_node(bst_node_t *root)
{
    bst_node_t *p;
    p = root;

    if (!p){
        return NULL;
    } else {
        while(p->left != NULL){
            p = p->left;
        }
    }
    return p;
}

bst_node_t *max_node(bst_node_t *root)
{
    bst_node_t *p;
    p = root;

    if (!p){
        return NULL;
    } else {
        while(p->right != NULL){
            p = p->right;
        }
    }
    return p;
}

bst_node_t *successor(bst_node_t *root, bst_node_t *node)
{
    bst_node_t *succ = NULL;

    if(!node)
        return NULL;

    if(node->right != NULL)
        return min_node(node->right);

    while (root != NULL){
        if (node->data < root->data){
            succ = root;
            root = root->left;
        } else if (node->data > root->data){
            root = root->right;
        } else break;
    }
    return succ;
}

bst_node_t *predecessor(bst_node_t *root, bst_node_t *node)
{
    bst_node_t *pred = NULL;

    if(!node)
        return NULL;

    if(node->left != NULL)
        return max_node(node->left);

    while (root != NULL){
        if (node->data > root->data){
            pred = root;
            root = root->right;
        } else if (node->data < root->data){
            root = root->left;
        } else break;
    }
    return pred;
}

bst_node_t *find_node(bst_node_t *root, int data)
{
    bst_node_t *p;
    p = root;

    while (p != NULL){
        if (data < p->data){
            p = p->left;
        } else if (data > p->data){
            p = p->right;
        } else {
            break;
        }
    }
    return p;
}

void inorder(bst_node_t *root)
{
    if (root == NULL){
        return;
    } else {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(bst_node_t *root)
{
    if (root == NULL){
        return;
    } else {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(bst_node_t *root)
{
    if (root == NULL){
        return;
    } else {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main(int argc, char **argv)
{
    bst_node_t *root = NULL;
    bst_node_t *p = NULL;
    bst_node_t *f;

    int a[11] = {25,13,43,10,21,54,2,15,19,17,18};

    for(int i=0; i<11; i++)
        insert_node(&root, a[i]);
    inorder(root);
    printf("\n");
    delete_node(&root, 25);
}
