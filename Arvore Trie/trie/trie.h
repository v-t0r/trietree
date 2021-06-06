typedef struct Trie Trie;

Trie* criaTrie();
void liberaTrie(Trie *tr);
int insereTrie(Trie *tr, char *str);
int buscaTrie(Trie *tr, char *str);
int removeTrie(Trie **tr, char *str);
void imprimeTrie(Trie *tr);
void autocompletarTrie (Trie *tr, char *prefixo);
