#include "node.h"
#include "mpool.h"
#include "rbtree.h"
#include <stdlib.h>

dfa_node_t *dfa_node_create(struct mpool *mp)
{
    dfa_node_t *node = NULL;
    if (mp) {
        node = (dfa_node_t *) mpool_malloc(mp, sizeof(dfa_node_t));
    } else {
        node = (dfa_node_t *) malloc(sizeof(dfa_node_t));
    }
    node->root = RB_ROOT;
    return node;
}

dfa_node_t *dfa_node_find_child(struct rb_root *root, char chr)
{
    struct rb_node *node = root->rb_node;

    while (node) {
        struct dfa_node *data = container_of(node, struct dfa_node, node);

        if (chr == data->chr) {
            return data;
        }
        if ((long)chr < (long)data->chr) {
            node = node->rb_left;
        } else {
            node = node->rb_right;
        }
    }

    return NULL;
}

int dfa_node_insert(struct rb_root *root, struct dfa_node *node)
{
    struct rb_node **new = &(root->rb_node), *parent = NULL;

    /* Figure out where to put new node */
    while (*new) {
        struct dfa_node *this = container_of(*new, struct dfa_node, node);

        if (node->chr == this->chr) { // already exists
            return 0;
        }

        parent = *new;
        if ((long)node->chr < (long)this->chr) {
            new = &((*new)->rb_left);
        } else {
            new = &((*new)->rb_right);
        }
    }

    /* Add new node and rebalance tree. */
    rb_link_node(&node->node, parent, new);
    rb_insert_color(&node->node, root);
    return 1;
}

void dfa_node_release(dfa_node_t *node)
{
}
