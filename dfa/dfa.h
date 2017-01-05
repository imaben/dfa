#ifndef __DFA_H__
#define __DFA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "node.h"

typedef void (*dfa_match_cb)(char *string, void *argument);

struct mpool;

enum dfa_match_type {
    MATCH_TYPE_MIN = 0,
    MATCH_TYPE_MAX = 1
};

typedef struct dfa_trie {
    dfa_node_t *root;
    struct mpool *mp;
} dfa_trie_t;

typedef struct dfa_match {
    dfa_pattern_t *pattern;
    size_t size;    /* Number of matched pattern(s) */

    /**** user specified ****/
    int pos;        /* Current position in the givin text
                     * The initial value must be specified to 0 */
    enum dfa_match_type mt;
} dfa_match_t;

#define MATCH_INIT_MIN {.pattern = NULL, .size = 0, .pos = 0, .mt = MATCH_TYPE_MIN}
#define MATCH_INIT_MAX {.pattern = NULL, .size = 0, .pos = 0, .mt = MATCH_TYPE_MIN}

dfa_trie_t *dfa_trie_create();
int dfa_trie_add(dfa_trie_t *trie, char *string, void *argument);
int dfa_trie_find_next(dfa_trie_t *trie, char *text, dfa_match_t *match);
int dfa_trie_match(dfa_trie_t *trie, char *text, enum dfa_match_type mt, dfa_match_cb cb);
void dfa_trie_release(dfa_trie_t *trie);

#ifdef __cplusplus
}
#endif
#endif
