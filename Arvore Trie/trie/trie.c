#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

// Define the character size
#define ALFABETO 27

// Data structure to store a Trie node
struct Trie
{
    int ehFolha;             // 1 qnd o no eh folha
    struct Trie* letra[ALFABETO];
};

// Function that returns a new Trie node
Trie* criaTrie()
{
    Trie* no = (Trie*)malloc(sizeof(Trie));
    no->ehFolha = 0;

    for (int i = 0; i < ALFABETO; i++) {
        no->letra[i] = NULL;
    }

    return no;
}

void liberaTrie(Trie *tr){
    int i;

    if(tr!=NULL){
        for(i=0; i<ALFABETO; i++){
            if(tr->letra[i] != NULL)
                liberaTrie(tr->letra[i]);
        }
     free (tr);
     tr=NULL;
    }
}

int insereTrie(Trie *tr, char* str)
{
    if(tr==NULL)
        return 0;
    // start from the root node
    struct Trie* atual = tr;
    while (*str != '\0')
    {
        // cria um novo no se o caminho nao existe
        if(*str=='-'){ //tratamento especial cajo seja hifen
            if(atual->letra[26]==NULL){
                atual->letra[26] = criaTrie();
                if(atual->letra[26]==NULL)
                    return 0;
            }
            atual = atual->letra[26];
            str++;
        }
        else{
            if (atual->letra[*str - 97] == NULL) {
                atual->letra[*str - 97] = criaTrie();
                if (atual->letra[*str - 97] == NULL)
                    return 0;
            }

        atual = atual->letra[*str - 97];
        str++;
        }
    }
    //marca como folha
    atual->ehFolha = 1;
    return 1;
}

int buscaTrie(struct Trie* tr, char* str)
{
    if (tr == NULL) {
        return 0;
    }

    struct Trie* atual = tr;
    while (*str != '\0')
    {
        if(*str == '-'){ //tratamento especial para hifen
            atual = atual->letra[26];
            if(atual==NULL){
                return 0; //nao existe
            }

        }
        else{
            atual = atual->letra[*str - 97];
            if (atual == NULL) {
                return 0; //nao existe
            }
        }
        str++;
    }
    if (atual->ehFolha == 1)
        return 1;
    else
        return 0;
}

int temFilho(struct Trie* atual)
{
    for (int i = 0; i < ALFABETO; i++)
    {
        if (atual->letra[i] != NULL) {
            return 1;
        }
    }
    return 0;
}

int removeTrie(struct Trie **tr, char* str)
{
    if (*tr == NULL) {
        return 0;
    }

    if (*str != '\0')
    {
        if(*str == '-'){ //tratamento especial para hifen
            if (*tr != NULL && (*tr)->letra[26] != NULL && removeTrie(&((*tr)->letra[26]), str + 1) == 1 && (*tr)->ehFolha == 0){
                if (temFilho(*tr) == 0)
                {
                    free(*tr);
                    (*tr) = NULL;
                    return 1;
                }
                else {
                    return 0;
                }
            }

        }
        else{
            if (*tr != NULL && (*tr)->letra[*str - 97] != NULL && removeTrie(&((*tr)->letra[*str - 97]), str + 1) == 1 && (*tr)->ehFolha == 0){
                if (temFilho(*tr) == 0)
                {
                    free(*tr);
                    (*tr) = NULL;
                    return 1;
                }
                else {
                    return 0;
                }
            }
        }
    }

    if (*str == '\0' && (*tr)->ehFolha)
    {
        if (temFilho(*tr) == 0)
        {
            free(*tr);
            (*tr) = NULL;
            return 1;
        }
        else { //tem filho e eh folha = uma palavra dentro de outra
            (*tr)->ehFolha = 0;
            return 0;
        }
    }

    return 0;
}


void autocompletarTrie (Trie* tr, char *prefixo){
    if (tr == NULL) {
        printf("Arvore vazia!");
        return;
    }
    int i=0;
    struct Trie* atual = tr;
    while (prefixo[i] != '\0')
    {
        if(prefixo[i]=='-'){
            atual = atual->letra[26];
            if (atual == NULL) {
                printf("Nao existe nenhuma palavra com este prefixo");
                return;
            }
        }
        else{
            atual = atual->letra[prefixo[i] - 97];
            if (atual == NULL) {
                printf("Nao existe nenhuma palavra com este prefixo");
                return;
            }
        }
        i++;
    }


    if (atual->ehFolha == 1)
        printf("%s\n", prefixo);

    for(i=0; i<ALFABETO; i++){
        if(atual->letra[i]!=NULL){
            char prefixN[48];
            strcpy(prefixN, prefixo);
            char c;
            if(i==26)
                c = '-';
            else
                c = i + 97;

            int tam = strlen(prefixN);
            prefixN[tam]=c;
            prefixN[tam+1]='\0';
            autocompletarTrie(tr, prefixN);
        }
    }
    return;
}

void imprimeTrie (Trie* tr){
    if(temFilho(tr)==0){
        printf("A arvore nao possui nenhum elemento");
        return;
    }
    int i;
    for(i=0; i<ALFABETO; i++){
        if(tr->letra[i]!=NULL){
            char c[2];
            c[0]=i+97;
            autocompletarTrie(tr, c);
        }
    }
     return;
}
