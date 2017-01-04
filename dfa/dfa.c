#include <stdlib.h>
#include <assert.h>
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

int dfa_trie_add(dfa_trie_t *trie, char *string, void *argument)
{
    assert(trie != NULL);
    assert(string != NULL);

    char *p = string;
    struct rb_root *root = &trie->root->root;
    dfa_node_t *n, *new;
    while (*p != '\0') {
        n = dfa_node_find_child(root, *p);
        if (NULL == n) { // insert new node
            new = dfa_node_create(trie->mp);
            dfa_node_set_chr(new, *p);
            dfa_node_insert(root, new);
            root = &new->root;
        } else {
            root = &n->root;
        }
        p++;
    }
    dfa_node_set_final(new, 1);
    dfa_pattern_t *patt = mpool_malloc(trie->mp, sizeof(dfa_pattern_t));
    patt->string = mpool_strdup(trie->mp, string);
    patt->argument = argument;
    dfa_node_set_pattern(new, patt);
    return 0;
}

int dfa_trie_match(dfa_trie_t *trie, char *text, dfa_match_cb cb)
{
    return 0;
}

void dfa_trie_release(dfa_trie_t *trie)
{
    mpool_free(trie->mp);
    free(trie);
}

