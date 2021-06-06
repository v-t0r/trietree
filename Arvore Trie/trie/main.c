#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

// Trie implementation in C – Insertion, Searching, and Deletion
int main()
{
    char palavra[47]; //Maior palavra da lingua portuguesa tem 46 letras
    struct Trie* tr = criaTrie();


    //Abre o arquivo com as palavras
    FILE *f;
    f = fopen("palavras.txt","r");
    if(f == NULL){
        printf("Erro na abertura do arquivo das palavras!\n");
        system("pause");
        exit(1);
    }

    //Insere cada uma das palavras do arquivo na arvore
    while(feof(f) == 0){
        fscanf(f,"%s", palavra); //recebe a palavra do arquivo
        if(insereTrie(tr, palavra)==1){ //insere a palavra
            printf("Palavra %s inserida com sucesso!\n", palavra);
        }
        else
            printf("Falha ao inserir a palavra %s!\n", palavra);
    }

    fclose(f);

    char opcao;
    do{
        printf("\n====O que deseja fazer?====\n");
        printf("[1]Verificar se uma palavra existe na arvore\n");
        printf("[2]Inserir uma nova palavra\n");
        printf("[3]Remover uma palavra da arvore\n");
        printf("[4]Imprimir todas as palavras da arvore\n");
        printf("[5]Autocompletar a partir de um prefixo\n");
        printf("[0]Sair do programa\n");
        printf("Sua opcao: ");
        setbuf(stdin, NULL);
        opcao=getchar();
        switch(opcao){
            case '1':
                //Busca a palavra digitada
                printf("\nPalavra que deseja buscar na arvore: ");
                setbuf(stdin, NULL);
                gets(palavra);
                if((buscaTrie(tr, palavra)) == 0)
                    printf("A palavra buscada NAO existe na arvore!\n");
                else{
                    printf("A palavra buscada existe na arvore!\n");
                }
                break;
            case '2':
                //Insere uma nova palavra na arvore
                printf("\nPalvra que deseja inserir: ");
                setbuf(stdin, NULL);
                gets(palavra);
                if(buscaTrie(tr, palavra)==1)
                    printf("A palavra digitada ja existe na arvore!\n");
                else{
                    if(insereTrie(tr, palavra)==1) //insere a palavra
                        printf("Palavra %s inserida com sucesso!\n", palavra);
                    else
                        printf("Falha ao inserir a palavra %s!\n", palavra);
                    }
                break;
            case '3':
                printf("\nPalavra que deseja remover: ");
                setbuf(stdin, NULL);
                gets(palavra);
                if(buscaTrie(tr, palavra)==0)
                    printf("A palavra digitada nao existe na arvore!\n");
                else{
                    removeTrie(&tr, palavra);
                    printf("Palavra removida com sucesso!\n");
                }
                break;
            case '4':
                printf("\nTodas as palavras da arvore:\n");
                imprimeTrie(tr);
                break;
            case '5':
                printf("Digite o prefixo que deseja autocompletar: ");
                setbuf(stdin, NULL);
                gets(palavra);
                printf("\nTodas as palavras com o prefixo %s:\n", palavra);
                autocompletarTrie(tr, palavra);
                break;
            case '0':
                printf("Encerrando programa...\n");
                liberaTrie (tr);
                system("pause");
                return 1;
                break;
            default:
                printf("Digite uma opcao valida!\n");
        }
    }while(opcao!='0');

    return 0;
}
