#ifndef __NODE_H__
#define __NODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rbtree.h"

struct mpool;

typedef struct dfa_pattern {
    char *string;
    void *argument;
} dfa_pattern_t;

typedef struct dfa_node {
    char chr;
    char final;
    struct rb_root root;
    struct rb_node node;
    dfa_pattern_t *patt; /* trade space for time, only for final == 0 */
} dfa_node_t;

#define dfa_node_set_chr(n, c) (n->chr = c)
#define dfa_node_set_final(n, f) (n->final = f)
#define dfa_node_set_pattern(n, p) (n->patt = p)
#define dfa_node_is_final(n) (n->final == 1)

dfa_node_t *dfa_node_create(struct mpool *mp);
dfa_node_t *dfa_node_find_child(struct rb_root *root, char chr);
int dfa_node_insert(struct rb_root *root, struct dfa_node *node);
void dfa_node_release(dfa_node_t *node);

#ifdef __cplusplus
}
#endif
#endif
