#ifndef CUP_TRAVERSALS_H
#define CUP_TRAVERSALS_H

#include "tree.h"

int do_preorder(struct tree *root, void (*func)(struct tree *));
int do_inorder(struct tree *root, void (*func)(struct tree *));
int do_postorder(struct tree *root, void (*func)(struct tree *));

struct tree *preorder_successor(struct tree *node);
struct tree *inorder_successor(struct tree *node);
struct tree *postorder_successor(struct tree *node);

#endif
