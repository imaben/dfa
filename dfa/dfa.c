#include <stdlib.h>
#include <assert.h>
#include <string.h>
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
        if (!n) { // insert new node
            new = dfa_node_create(trie->mp);
            dfa_node_set_chr(new, *p);
            dfa_node_insert(root, new);
            root = &new->root;
        } else {
            root = &n->root;
        }
        p++;
    }

    n = container_of(root, struct dfa_node, root);
    dfa_node_set_final(n, 1);

    dfa_pattern_t *patt = mpool_malloc(trie->mp, sizeof(dfa_pattern_t));
    patt->string = mpool_strdup(trie->mp, string);
    patt->argument = argument;

    dfa_node_set_pattern(n, patt);
    return 0;
}

static int dfa_trie_find_next_bs(dfa_trie_t *trie, char *text,
        enum dfa_match_type mt, dfa_node_t **nnode)
{
    int i, len = strlen(text);
    int match_len = 0, flag = 0;
    dfa_node_t *node = NULL;
    struct rb_root *root = &trie->root->root;
    for (i = 0; i < len; i++) {
        char chr = text[i];
        node = dfa_node_find_child(root, chr);
        if (!node) { // does not exists
            break;
        }
        // found
        match_len++;
        if (dfa_node_is_final(node)) {
            flag = 1;
            *nnode = node;
            if (mt == MATCH_TYPE_MIN) {
                break;
            }
        }
        root = &node->root;
    }
    if (!flag) {
        match_len = 0;
    }
    return match_len;
}

int dfa_trie_find_next(dfa_trie_t *trie, char *text, dfa_match_t *match)
{
    if (!trie || !text || !match)
        return -1;

    int len = strlen(text), ml = 0;
    dfa_node_t *node;
    while (match->pos < len) {
        if ((ml = dfa_trie_find_next_bs(trie, text + match->pos,
                        match->mt, &node)) > 0) {
            match->size = ml;
            match->pos++;
            match->pattern = node->patt;
            return 1;
        }
        match->pos++;
    }
    return 0;
}

int dfa_trie_match(dfa_trie_t *trie, char *text, enum dfa_match_type mt, dfa_match_cb cb)
{
    dfa_match_t match;
    if (mt == MATCH_TYPE_MIN)
        match = MATCH_INIT_MIN;
    else
        match = MATCH_INIT_MAX;

    int count = 0;
    while (dfa_trie_find_next(trie, text, &match)) {
        cb(match.pattern->string, match.pattern->argument);
        count++;
    }
    return count;
}

void dfa_trie_release(dfa_trie_t *trie)
{
    mpool_free(trie->mp);
    free(trie);
}

