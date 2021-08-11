#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define debug 0


//funcao responsavel por andar pela string e verificar se o caracteres sao iguais
int Palindromo(char* palavraAtual, char* palavraAtualInvertida, int tamanho, int pos){
    if(pos < tamanho){
        if(palavraAtual[pos] == palavraAtualInvertida[pos]){
            return 1 * Palindromo(palavraAtual, palavraAtualInvertida, tamanho, pos+1);
        }else
            return 0;
    } else
        return 1;
}
//funcao resposavel por verificar a posicao do espacos dos palindromos indiretos
int palindromoIndireto(int *posicaoEspaco, int *posicaoEspacoInvert, int tamanho, int pos){
    if(pos < tamanho){
        if(posicaoEspaco[pos] == posicaoEspacoInvert[pos]){
            return 1 * palindromoIndireto(posicaoEspaco, posicaoEspacoInvert, tamanho, pos+1);
        }else
            return 0;
    }else
        return 1;
}

//funcao ja usada em outros execicios, le uma string e aloca e realoca dinamicamente conforme for necessario
//le em blocos de 4bytes
//Tambem faz a verificacao e troca de \n por \0
//Retorna um ponteiro com a string alocada
char *readline(){
    char *String = NULL;
    char buffer[5];
    char Letra;
    int i = 0;
    int tamanho = 0;

    do{
        scanf("%c", &Letra);
        buffer[i] = Letra == '\n' ? '\0' : Letra;
        i ++;
        if(i == 4 || Letra == '\n'){
            tamanho += i;
            String = (char*) realloc(String, tamanho);
            memcpy(String + tamanho - i, buffer, i);
            i = 0;
        }
    }while(Letra != '\n');

    return String;
}

//funcao responsavel por dar shift na string ao verificar se o caracter, verifica a posicao das barras e espacos e guarda as posicoes no vetor
void padronizarString(int tamanhoPalavra, char *palavra, int *posicaoEspaco){
    int k = 0;

    for(int i = 0; i < tamanhoPalavra; i++){
        if(palavra[i] == ' '|| palavra[i] == '/'){
            posicaoEspaco[k++] = i;
        }

        if(!isalnum(palavra[i])){
            for(int j = i; j < tamanhoPalavra; j++){
                palavra[j] = palavra[j+1];
            }
            tamanhoPalavra--;
            i--;
        }
    }
}

int main(){

    char* palavra;
    char* palavraInvertida;
    int tamanhoPalavra, novoTamanhoPalavra;
    int posicao = 0;

    //lendo a palavra e alocando dinamicamente
    palavra = readline();

    //normalizando as letras de entrada para maiusculo
    for(int i = 0; palavra[i]; i++){
        palavra[i] = toupper(palavra[i]);
    }

    tamanhoPalavra = strlen(palavra);
    if(debug){
        printf("%d\n", tamanhoPalavra);
    }

    int *posicaoEspaco = calloc(tamanhoPalavra, sizeof(int));
    int *posicaoEspacoInvert = calloc(tamanhoPalavra, sizeof(int));

    palavraInvertida = calloc(tamanhoPalavra+1, sizeof(char));

    int j = 0;
    //inverte a string palavra e insere dentro da string palavraInvertida
    for(int i = tamanhoPalavra-1; i >= 0; i--){
        palavraInvertida[i] = palavra[j++];
    }

    if(debug){
        printf("%s\n", palavra);
        printf("%s\n", palavraInvertida);
    }
    //funcoes responsaveis por retirar caracteres nao alfanumericos
    padronizarString(tamanhoPalavra, palavra, posicaoEspaco);
    padronizarString(tamanhoPalavra, palavraInvertida, posicaoEspacoInvert);

    novoTamanhoPalavra = strlen(palavra);
    if(debug){
        printf("%d\n", novoTamanhoPalavra);
    }

    if(debug){
        printf("%s\n", palavra);
        printf("%s\n", palavraInvertida);
    }

    int result = Palindromo(palavra, palavraInvertida, novoTamanhoPalavra, posicao);

    //verifica se result nao eh palindromo, caso seja verifica se eh direto ou nao
    if(!result){
        printf("Nao eh um palindromo\n");
    }else if (result){
        if(palindromoIndireto(posicaoEspaco, posicaoEspacoInvert, tamanhoPalavra, posicao)){
            printf("Palindromo direto\n");
        }
        else{
            printf("Palindromo indireto\n");
        }
    }

    free(palavraInvertida);
    free(palavra);
    free(posicaoEspaco);
    free(posicaoEspacoInvert);

    return 0;
}
