#ifndef AVL_H
#define AVL_H
struct node;

void avl_insert(struct node *root, int data);
struct node *avl_remove(struct node *root);
#endif
