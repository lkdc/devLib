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
static inline void balance_path(avl_root_t *root, avl_node_t *node);

void insert_node(avl_root_t *root, int data);
void delete_node(avl_root_t *root, int data);

avl_node_t *leftmost(avl_node_t *node);
avl_node_t *rightmost(avl_node_t *node);

avl_node_t *successor(avl_root_t *root, avl_node_t *node);
avl_node_t *predecessor(avl_root_t *root, avl_node_t *node);
avl_node_t *find(avl_root_t *root, int data);

void inorder(avl_node_t *node);
void preorder(avl_node_t *node);
void postorder(avl_node_t *node);

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

void insert_node(avl_root_t *root, int data)
{
    avl_node_t **p = &root->node;
    avl_node_t *parent = NULL;

    //--------find insertion point--------//

    while (*p){
        parent = *p;
        if (data < (*p)->data){
            p = &(*p)->left;
        } else if(data > (*p)->data){
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
    (*p)->parent = parent;

    printf("Insert Node: %d\n", (*p)->data);

    //--------balance the path from the node back to the root--------//

    balance_path(root, parent);

}

void delete_node(avl_root_t *root, int data)
{
    avl_node_t **p = &root->node;

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
    avl_node_t *parent = NULL;
    avl_node_t *tmp = NULL;

    //--------remove the links and free the node--------//

    if(*p)
        printf("Delete Node: %d\n", (*p)->data);

    while (1){
        if(!(*p)){
            printf("Node not found\n");
            return;
        }
        if (!(*p)->right){
            if((*p)->left != NULL){
                (*p)->left->parent = (*p)->parent;
            }
            parent = (*p)->parent;
            tmp = *p;
            *p = (*p)->left;
            free(tmp);
            break;
        } else {
            link = link_leftmost(&(*p)->right);
            (*p)->data = (*link)->data;
            p = link;
            parent = (*p)->parent;
            continue;
        }
    }

    //--------balance the path from the removed node back to the root--------//

    balance_path(root, parent);

}

static inline void balance_path(avl_root_t *root, avl_node_t *node)
{

    avl_node_t **link = NULL;
    avl_node_t *parent = NULL;

    while(1){
        if (!node){
            return;
        }
        update_height(node);
        printf("        Node, Balance: %d, (%d)\n", node->data, balance(node));
        if (balance(node) < -1){                    //if node is right heavy
            if (balance(node->right) > 0){          //if right child is left heavy
                link = &node->right;                //node->child link
                printf("    Right Rotate: %d\n", (*link)->data);
                right_rotate(link);                 //right rotate the right child
            }
            if (!node->parent){                     //parent->node link
                link = &root->node;
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
                link = &root->node;
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

avl_node_t *successor(avl_root_t *root, avl_node_t *node)
{
    avl_node_t *p = root->node;
    avl_node_t *succ = NULL;

    if(!node)
        return NULL;

    if(node->right != NULL)
        return leftmost(node->right);

    while (p != NULL){
        if (node->data < p->data){
            succ = p;
            p = p->left;
        } else if (node->data > p->data){
            p = p->right;
        } else break;
    }
    return succ;
}

avl_node_t *predecessor(avl_root_t *root, avl_node_t *node)
{
    avl_node_t *p = root->node;
    avl_node_t *pred = NULL;

    if(!node)
        return NULL;

    if(node->left != NULL)
        return rightmost(node->left);

    while (p != NULL){
        if (node->data > p->data){
            pred = p;
            p = p->right;
        } else if (node->data < p->data){
            p = p->left;
        } else break;
    }
    return pred;
}

avl_node_t *find_node(avl_root_t *root, int data)
{
    avl_node_t *p = root->node;

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

void inorder(avl_node_t *node)
{
    if (node == NULL){
        return;
    } else {
        inorder(node->left);
        printf("%d:", node->data);
        printf("(%d)  ", node->height);
        inorder(node->right);
    }
}

void preorder(avl_node_t *node)
{
    if (node == NULL){
        return;
    } else {
        printf("%d:", node->data);
        printf("(%d)  ", node->height);
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(avl_node_t *node)
{
    if (node == NULL){
        return;
    } else {
        postorder(node->left);
        postorder(node->right);
        printf("%d:", node->data);
        printf("(%d)  ", node->height);
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

    avl_root_t my_root = {NULL, };
    avl_root_t *root = &my_root;

    avl_node_t *p = NULL;

    int a[16] = {1,2,3,10,9,8,6,5,4,12,13,14,16,15,11,7};

    for(int i = 0; i<16; i++){
        insert_node(root, a[i]);
    }

    delete_node(root, 6);
    delete_node(root, 14);
    delete_node(root, 8);

    for(int i=0; i<10000; i++){
        p = find_node(root,i);
        if(p){
            path(p);
        }
    }

    return 0;

}
