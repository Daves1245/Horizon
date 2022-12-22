#include <stdlib.h>
#include "stack.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * /
*
* file: stack.c
*
* author: David Santamaria (davidsantamaria1245@gmail.com)
* 
* purpose:
*       provide a C implementation of the common stack datastructure
*
* version 1.0.1
* changes since last version: 
        * enforced consistent style.
        * fixed bugs by checking for nullpointer parameters in functions.
        * improved pop() function by correctly indexing the elements in 
        *       their proved places.
* 
* possibly confusing code:
        * sizeof(*ptr) instead of sizeof(type)
*               - we use this to minimize the number of times we would
*               have to rewrite sizeof(type), should the type change.
*               This reduces the amount of redundant code and is used often
*               in this library.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// create a stack and return a reference to it
stack *stack_new()
{
        stack * ret = malloc(sizeof(*ret));
        ret->capacity = STACK_INIT_CAPACITY;
        ret->items = malloc(sizeof(*(ret->items)) * ret->capacity);
        if (!ret->items) {
                fprintf(stderr, "stack: error on initializing items array.\n");
                printf("ERROR\n");
        }
        ret->size = 0;
        return ret;
}

// Grab the size of the stack
// Returns negative on failure
int stack_size(stack *s)
{
        if (s) {
                return s->size;
        } else {
                return -1;
        }
}

// Resize the stack - return 0 on success
int stack_resize(stack *s, int capacity)
{
        void ** items = realloc(s->items, sizeof(*items) * capacity);
        if (items) {
                s->items = items;
                s->capacity = capacity;
        } else {
                fprintf(stderr, "stack error: items not initialized");
                return -1;
        }
        return 0;
}

// Put an element onto the stack.
// Return 0 on success
int stack_put(stack *s, void *item)
{
        if (!s) {
                return -1;
        }
        if (s->size >= s->capacity) {
                stack_resize(s, s->capacity * 2);
        }
        s->size++;
        s->items[s->size - 1] = item;
        return 0;
}

// Return a pointer to the topmost element
// in the stack. Returns NULL on failure.
void *stack_pop(stack *s)
{
        void *ret = NULL;
        if (!s || s->size <= 0) {
                return ret;
        }

        // grab the topmost element
        ret = s->items[s->size - 1];
        // remove it from the stack
        s->items[s->size - 1] = NULL;   /* sanity check: this is not
                                         * a memory problem because items[i]
                                         * was not allocated onto the heap, unless the user
                                         * did so outside of this scope. If so, it is up to
                                         * the user to free it at their own doing.
                                         * the only allocation done by the stack
                                         * is the items pointer to pointer, which is taken
                                         * care of in the delete method. 
                                         */
        --s->size;

        if (s->size < s->capacity / 4) {
                stack_resize(s, s->capacity / 2);
        }

        return ret;
}

int stack_empty(stack *s)
{
        if (s) {
                return s->size == 0;
        } else {
                return -1;
        }
}

// Free the stack and all of its
// elements
void stack_delete(stack *s)
{
        if (!s) {
                return;
        }
        s->size = s->capacity = 0;
        free(s->items);
}

