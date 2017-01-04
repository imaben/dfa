#ifndef __DFA_H__
#define __DFA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "node.h"

struct mpool;

typedef struct dfa_trie {
    dfa_node_t *root;
    struct mpool *mp;
} dfa_trie_t;

dfa_trie_t *dfa_trie_create();
void dfa_trie_release(dfa_trie_t *trie);

#ifdef __cplusplus
}
#endif
#endif
