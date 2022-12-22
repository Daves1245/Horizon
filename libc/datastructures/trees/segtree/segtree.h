#ifndef CUP_SEGTREE_H
#define CUP_SEGTREE_H

/* Build a tree out of the pointer given */
void segtree_build(int *tree, int n);
/* Update the value at index i within the tree */
void segtree_update(int *tree, int i, int value);
/* Query the sum on the inteveral [l, r) */
int segtree_query(int *tree, int n, int l, int r);

#endif
