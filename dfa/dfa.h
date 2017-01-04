#ifndef __DFA_H__
#define __DFA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "node.h"

typedef void (*dfa_match_cb)(char *string, void *argument);

struct mpool;

typedef struct dfa_trie {
    dfa_node_t *root;
    struct mpool *mp;
} dfa_trie_t;

dfa_trie_t *dfa_trie_create();
int dfa_trie_add(dfa_trie_t *trie, char *string, void *argument);
int dfa_trie_match(dfa_trie_t *trie, char *text, dfa_match_cb cb);
void dfa_trie_release(dfa_trie_t *trie);

#ifdef __cplusplus
}
#endif
#endif
