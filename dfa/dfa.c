#include <stdlib.h>
#include "dfa.h"
#include "mpool.h"
#include "node.h"

dfa_trie_t *dfa_trie_create()
{
    dfa_trie_t *trie = (dfa_trie_t *) malloc(sizeof(dfa_trie_t));
    if (NULL == trie)
        return NULL;

    trie->mp = mpool_create(0);
    trie->root = dfa_node_create(trie->mp);
    return trie;
}

void dfa_trie_release(dfa_trie_t *trie)
{
    mpool_free(trie->mp);
    free(trie);
}

