#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Essa funcao le strings em blocos de 4bytes
  Tambem faz a verificacao e troca de \n por \0
  Retorna um ponteiro com a string alocada
*/

char *read_line(){
    char *Linha = NULL;
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
            Linha = (char*) realloc(Linha, tamanho);
            memcpy(Linha + tamanho - i, buffer, 4);
            i = 0;
        }
    }while(Letra != '\n');

    return Linha;
}

int main(){

    int numeroLinhas;
    scanf("%d\n", &numeroLinhas);
    if(numeroLinhas <= 0){
        printf("Erro");
        return 0;
    }

    char **Linhas;
    Linhas = calloc(numeroLinhas, sizeof(char*));
    if(Linhas == NULL){
        printf("Erro");
        return 0;
    }

    for(int i = 0; i < numeroLinhas; i++){
        Linhas[i] = read_line();
    }

    int numeroDelinhasValidas;
    scanf("%d", &numeroDelinhasValidas);

    //Construindo um vetor com as linhas validas
    int linhasValidas[numeroDelinhasValidas];
    for (int i = 0; i < numeroDelinhasValidas; i++) {
        scanf(" %d", &linhasValidas[i]);
    }
    //Printa as linhas validas
    for(int i = 0; i < numeroDelinhasValidas; i++){
        printf("%s\n", Linhas[linhasValidas[i]]);
    }
    for(int i = 0; i < numeroLinhas; i++){
        free(Linhas[i]);
    }
    free(Linhas);
    return 0;
}
