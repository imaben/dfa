#include <stdio.h>
#include "dfa.h"

char *words[] = {
    "city",
    "clutter",
    "ever",
    "experience",
    "neo",
    "one",
    "simplicity",
    "utter",
    "whatever",
    "what",
    NULL
};

char *chunk1 = "experience the ease and simplicity of multifast";
char *chunk2 = "whatever you are be a good one";
char *chunk3 = "out of clutter, find simplicity";

void dfa_match_handler(char *string, void *argument)
{
    printf("matched:%s\n", string);
}

int main(int argc, char **argv)
{
    dfa_trie_t *trie = dfa_trie_create();
    int i = 0;
    char *word;
    while ((word = words[i++])) {
        dfa_trie_add(trie, word, NULL);
    }
    printf("------------\n");
    dfa_trie_match(trie, chunk2, MATCH_TYPE_MAX, dfa_match_handler);

    dfa_trie_match(trie, chunk1, MATCH_TYPE_MIN, dfa_match_handler);
    printf("------------\n");
    dfa_trie_match(trie, chunk2, MATCH_TYPE_MIN, dfa_match_handler);
    printf("------------\n");
    dfa_trie_match(trie, chunk2, MATCH_TYPE_MAX, dfa_match_handler);
    printf("------------\n");
    dfa_trie_match(trie, chunk3, MATCH_TYPE_MIN, dfa_match_handler);

    dfa_trie_release(trie);
    return 0;
}
