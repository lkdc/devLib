// iterative AVL TREE with insert and delete

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
static inline avl_node_t **link_leftmost(avl_node_t **node);
static inline void balance_path(avl_node_t **root, avl_node_t *node);

void insert_node(avl_node_t **root, int data);
void delete_node(avl_node_t **root, int data);

avl_node_t *leftmost(avl_node_t *root);
avl_node_t *rightmost(avl_node_t *root);
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
    if (!node){
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
    avl_node_t *p = (*link)->left;

    p->parent = (*link)->parent;
    (*link)->parent = p;
    if (p->right != NULL){
        p->right->parent = *link;
    }
    (*link)->left = p->right;
    p->right = *link;
    update_height(*link);
    *link = p;
}

static inline void left_rotate(avl_node_t **link)
{
    avl_node_t *p = (*link)->right;

    p->parent = (*link)->parent;
    (*link)->parent = p;
    if (p->left != NULL){
        p->left->parent = *link;
    }
    (*link)->right = p->left;
    p->left = *link;
    update_height(*link);
    *link = p;
}

static inline avl_node_t **link_leftmost(avl_node_t **node)
{
    if (!(*node)){
        return NULL;
    } else {
        while((*node)->left != NULL){
            node = &(*node)->left;
        }
    }
    return node;
}

void insert_node(avl_node_t **root, int data)
{
    avl_node_t **p = root;
    avl_node_t *last = NULL;

    //--------find insertion point--------//

    while (*p){
        if (data < (*p)->data){
            last = *p;
            p = &(*p)->left;
        } else if(data > (*p)->data){
            last = *p;
            p = &(*p)->right;
        } else {
            printf("Node already exist\n");
            return;
        }
    }

    //--------create a new node and link it--------//

    *p = malloc(sizeof(avl_node_t));
    assert(*p);
    (*p)->data = data;
    (*p)->left = NULL;
    (*p)->right = NULL;
    (*p)->parent = last;

    //--------balance the path from the node back to the root--------//

    balance_path(root, last);

}

void delete_node(avl_node_t **root, int data)
{
    avl_node_t **p = root;

    //--------find the node--------//

    if(!p){
        printf("Node not found\n");
        return;
    } else {
        while (*p){
            if (data < (*p)->data){
                p = &(*p)->left;
            } else if(data > (*p)->data){
                p = &(*p)->right;
            } else break;
        }
    }

    avl_node_t **link = NULL;
    avl_node_t *last = NULL;
    avl_node_t *tmp = NULL;

    //--------remove the links and free the node--------//

    while (1){
        if(!(*p)){
            printf("Node not found\n");
            return;
        }
        if (!(*p)->right){
            if((*p)->left != NULL){
                (*p)->left->parent = (*p)->parent;
            }
            last = (*p)->parent;
            tmp = *p;
            *p = (*p)->left;
            free(tmp);
            break;
        } else {
            link = link_leftmost(&(*p)->right);
            (*p)->data = (*link)->data;
            p = link;
            last = (*p)->parent;
            continue;
        }
    }

    //--------balance the path from the removed node back to the root--------//

    balance_path(root, last);

}

static inline void balance_path(avl_node_t **root, avl_node_t *node)
{

    avl_node_t **link = NULL;
    avl_node_t *parent = NULL;

    while(1){
        if (!node){
            return;
        }
        update_height(node);
//        printf("        Node, Balance: %d, (%d)\n", node->data, balance(node));
        if (balance(node) < -1){                    //if node is right heavy
            if (balance(node->right) > 0){          //if right child is left heavy
                link = &node->right;                //node->child link
//                printf("    Right Rotate: %d\n", (*link)->data);
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
//            printf("    Left Rotate: %d\n", (*link)->data);
            left_rotate(link);                      //left rotate the node
            continue;

        } else if (balance(node) > 1){              //if node is left heavy
            if (balance(node->left) < 0){           //if left child is right heavy
                link = &node->left;                 //node->child link
//                printf("    Left Rotate: %d\n", (*link)->data);
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
//            printf("    Right Rotate: %d\n", (*link)->data);
            right_rotate(link);                     //right rotate the node
            continue;
        }
        node = node->parent;
    }
}

avl_node_t *leftmost(avl_node_t *node)
{
    if (!node){
        return NULL;
    } else {
        while(node->left != NULL){
            node = node->left;
        }
    }
    return node;
}

avl_node_t *rightmost(avl_node_t *node)
{
    if (!node){
        return NULL;
    } else {
        while(node->right != NULL){
            node = node->right;
        }
    }
    return node;
}

avl_node_t *successor(avl_node_t *root, avl_node_t *node)
{
    avl_node_t *succ = NULL;

    if(!node)
        return NULL;

    if(node->right != NULL)
        return leftmost(node->right);

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
        return rightmost(node->left);

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
        printf("%d:", root->data);
        printf("(%d)  ", root->height);
        inorder(root->right);
    }
}

void preorder(avl_node_t *root)
{
    if (root == NULL){
        return;
    } else {
        printf("%d:", root->data);
        printf("(%d)  ", root->height);
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
        printf("%d:", root->data);
        printf("(%d)  ", root->height);
    }
}

void path(avl_node_t *node)
{
    while(node != NULL){
        printf("%d:", node->data);
        printf("(%d)  ", node->height);
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

    int a[16] = {12,9,18,6,10,16,22,4,7,11,13,17,20,26,19,15};

    for(int i = 0; i<16; i++){
        insert_node(&root, a[i]);
    }

    delete_node(&root, 17);

    for(int i=0; i<10000; i++){
        f = find_node(root,i);
        if(f) path(f);
    }

    return 0;

}
