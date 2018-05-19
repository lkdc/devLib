#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>

typedef struct avl_node avl_node_t;
typedef struct avl_root avl_root_t;

struct avl_node{
    avl_node_t *parent;
    avl_node_t *left;
    avl_node_t *right;
    int height;
    int data;
};

struct avl_root{
    avl_node_t *node;
};

static inline int max(int v1, int v2);
static inline int height(avl_node_t *node);
static inline void update_height(avl_node_t *node);
static inline int balance(avl_node_t *node);
static inline void right_rotate(avl_node_t **link);
static inline void left_rotate(avl_node_t **link);

void insert_node(avl_node_t **root, int data);
//void delete_node(avl_node_t **root, int data);
avl_node_t *min_node(avl_node_t *root);
avl_node_t *max_node(avl_node_t *root);
avl_node_t *successor(avl_node_t *root, avl_node_t *node);
avl_node_t *predecessor(avl_node_t *root, avl_node_t *node);
avl_node_t *find(avl_node_t *root, int data);

void inorder(avl_node_t *root);
void preorder(avl_node_t *root);
void postorder(avl_node_t *root);

static inline int max(int v1, int v2)
{
    if (v1 > v2)
        return v1;
    return v2;
}

static inline int height(avl_node_t *node)
{
    if (node == NULL)
        return -1;
    return node->height;
}

static inline void update_height(avl_node_t *node)
{
    if (node == NULL){
        return;
    }
    node->height = max(height(node->left), height(node->right)) + 1;
}

static inline int balance(avl_node_t *node)
{
    return (height(node->left) - height(node->right));
}

static inline void right_rotate(avl_node_t **link)
{
    avl_node_t *child = (*link)->left;
    avl_node_t *g_child = child->right;


    child->parent = (*link)->parent;
    (*link)->parent = child;
    if (g_child){
        g_child->parent = *link;
    }
    (*link)->left = child->right;
    child->right = *link;
    update_height(*link);
    *link = child;
}

static inline void left_rotate(avl_node_t **link)
{
    avl_node_t *child = (*link)->right;
    avl_node_t *g_child = child->left;

    child->parent = (*link)->parent;
    (*link)->parent = child;
    if (g_child){
        g_child->parent = *link;
    }
    (*link)->right = child->left;
    child->left = *link;
    update_height(*link);
    *link = child;
}

static inline int balance(avl_node_t *node)
{
    return (height(node->left) - height(node->right));
}

static inline void new_node(avl_node_t **link, avl_node_t *parent, int data)
{
    avl_node_t *node;
    node = malloc(sizeof(avl_node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    *link = node;
}

void insert_node(avl_node_t **root, int data)
{
    avl_node_t **p = root;
    avl_node_t *parent = NULL;

    //--------find insertion point

    while (*p){
        if (data < (*p)->data){
            parent = *p;
            p = &(*p)->left;
        } else if(data > (*p)->data){
            parent = *p;
            p = &(*p)->right;
        } else {
            printf("Node already exist\n");
            return;
        }
    }

    //--------create a new node and link it

    new_node(p, parent, data);
    printf("Insert Node: %d\n", (*p)->data);

    //---------balance the path from the node back to the root

    avl_node_t *node = *p;
    avl_node_t **link;

    while(1){
        update_height(node);
        printf("        Node, Balance: %d, (%d)\n", node->data, balance(node));
        if (balance(node) < -1){                    //if node is right heavy
            if (balance(node->right) > 0){          //if right child is left heavy
                link = &node->right;                //node->child link
                printf("    Right Rotate: %d\n", (*link)->data);
                right_rotate(link);                 //right rotate the right child
            }
            if (!node->parent){                     //parent->node link
                link = root;
            } else {
                parent = node->parent;
                if (parent->data < node->data)
                    link = &parent->right;
                else
                    link = &parent->left;
            }
            printf("    Left Rotate: %d\n", (*link)->data);
            left_rotate(link);                      //left rotate the node
            continue;

        } else if (balance(node) > 1){              //if node is left heavy
            if (balance(node->left) < 0){           //if left child is right heavy
                link = &node->left;                 //node->child link
                printf("    Left Rotate: %d\n", (*link)->data);
                left_rotate(link);                  //left rotate the left child
            }
            if (!node->parent){                     //parent->node link
                link = root;
            } else {
                parent = node->parent;
                if (parent->data > node->data)
                    link = &parent->left;
                else
                    link = &parent->right;
            }
            printf("    Right Rotate: %d\n", (*link)->data);
            right_rotate(link);                     //right rotate the node
            continue;
        }
        node = node->parent;
        if (!node) break;
    }
}

/*
void delete_node(avl_node_t **root, int data)
{
    avl_node_t **p = root;
    avl_node_t *p_free = NULL;
    avl_node_t *p_min = NULL;

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

*/

avl_node_t *min_node(avl_node_t *root)
{
    avl_node_t *p;
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

avl_node_t *max_node(avl_node_t *root)
{
    avl_node_t *p;
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

avl_node_t *successor(avl_node_t *root, avl_node_t *node)
{
    avl_node_t *succ = NULL;

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

avl_node_t *predecessor(avl_node_t *root, avl_node_t *node)
{
    avl_node_t *pred = NULL;

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

avl_node_t *find_node(avl_node_t *root, int data)
{
    avl_node_t *p;
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

void inorder(avl_node_t *root)
{
    if (root == NULL){
        return;
    } else {
        inorder(root->left);
        printf("%d ", root->data);
        printf("(%d), ", root->height);
        inorder(root->right);
    }
}

void preorder(avl_node_t *root)
{
    if (root == NULL){
        return;
    } else {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(avl_node_t *root)
{
    if (root == NULL){
        return;
    } else {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void path(avl_node_t *node)
{
    while(node != NULL){
        printf("%d ", node->data);
        printf("(%d), ", node->height);
        node = node->parent;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    avl_node_t *root = NULL;
    avl_node_t *p = NULL;
    avl_node_t *f;
    srand(time(NULL));

    int a[100] = {10, 15, 12, 6, 13, 14, 18, 19, 20};

    for(int i = 0; i<9; i++){
        insert_node(&root, a[i]);
    }

    for(int i = -1000; i<1000; i++){
        f = find_node(root, i);
        if (f)
            path(f);
    }

    return 0;

}
