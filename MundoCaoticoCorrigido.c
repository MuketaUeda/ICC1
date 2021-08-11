#include <stdio.h>
#include <stdlib.h>
#define debug 0


typedef struct{
int Linhas;
int Colunas;
int NumeroGeracoes;
char TipoDeModelo;
char** MatrizTabuleiro;
}Dados;

Dados* AlocaDados();
void PreencheMatriz(Dados* NovosDados);
void ImprimeMatriz(Dados* NovosDados);
int ModeloMoore(Dados* Moore, int linha, int coluna);
int ModeloNeumann(Dados* Neumann, int linha, int coluna);


int main(){
    int Vizinhos;
    Dados* NovosDados = AlocaDados();
    if(NovosDados == NULL){
        printf("Dados de entrada apresentam erro.");
        return 0;
    }
    PreencheMatriz(NovosDados);
    char Matriz[NovosDados->Linhas][NovosDados->Colunas];
    }
    if(NovosDados->TipoDeModelo == 'M'){
        for(int k = 0; k < NovosDados->NumeroGeracoes; k++){
            for(int i = 0; i < NovosDados->Linhas; i++){
                for(int j = 0; j < NovosDados->Colunas; j++){
                    Vizinhos = ModeloMoore(NovosDados, i, j);
                    if(NovosDados->MatrizTabuleiro[i][j] == 'x'){
                        if(Vizinhos < 2 || Vizinhos > 3){
                            Matriz[i][j] = '.';
                            continue;
                        }
                        else{
                            Matriz[i][j] = 'x';
                            continue;
                        }
                    }
                    if(NovosDados->MatrizTabuleiro[i][j] == '.'){
                        if(Vizinhos == 3){
                        Matriz[i][j] = 'x';
                        continue;
                        }
                        else{
                        Matriz[i][j] = '.';
                        }
                    }
                }
            }
            for(int i = 0; i < NovosDados->Linhas; i++) {
                for(int j = 0; j < NovosDados->Colunas; j++) {
                    NovosDados->MatrizTabuleiro[i][j] = Matriz[i][j];

                }
            }

        }
        ImprimeMatriz(NovosDados);

    }

    if(NovosDados->TipoDeModelo == 'N'){
        for(int k = 0; k < NovosDados->NumeroGeracoes; k++){
            for(int i = 0; i < NovosDados->Linhas; i++){
                for(int j = 0; j < NovosDados->Colunas; j++){
                    Vizinhos = ModeloNeumann(NovosDados, i, j);
                    if(NovosDados->MatrizTabuleiro[i][j] == 'x'){
                        if(Vizinhos < 2 || Vizinhos > 3){
                            Matriz[i][j] = '.';
                            continue;
                        }
                        else{
                            Matriz[i][j] = 'x';
                            continue;
                        }
                    }
                    if(NovosDados->MatrizTabuleiro[i][j] == '.'){
                        if(Vizinhos == 3){
                        Matriz[i][j] = 'x';
                        continue;
                        }
                        else{
                        Matriz[i][j] = '.';
                        }
                    }
                }
            }
            for(int i = 0; i < NovosDados->Linhas; i++) {
                for(int j = 0; j < NovosDados->Colunas; j++) {
                    NovosDados->MatrizTabuleiro[i][j] = Matriz[i][j];

                }
            }

        }
        ImprimeMatriz(NovosDados);

    }

    for(int i = 0; i < NovosDados->Linhas; i++) {
        free(NovosDados->MatrizTabuleiro[i]);
    }
    free(NovosDados->MatrizTabuleiro);
    free(NovosDados);

    return 0;
}


Dados* AlocaDados(){

    Dados* InfoGeracao;
    InfoGeracao = (Dados*) malloc(sizeof (Dados));
    InfoGeracao->Linhas = 0;
    InfoGeracao->Colunas = 0;
    InfoGeracao->NumeroGeracoes = 0;
    InfoGeracao->TipoDeModelo = 'a';

    scanf("%d %d", &InfoGeracao->Linhas, &InfoGeracao->Colunas);
    if(InfoGeracao->Linhas <= 0 || InfoGeracao->Colunas <= 0){
        free(InfoGeracao);
        return NULL;
    }

    scanf("%d", &InfoGeracao->NumeroGeracoes);
    if(InfoGeracao->NumeroGeracoes <= 0){
        free(InfoGeracao);
        return NULL;
    }
    if(debug){
        printf("%d\n", InfoGeracao->NumeroGeracoes);
    }

    scanf(" %c", &InfoGeracao->TipoDeModelo);
    if(InfoGeracao->TipoDeModelo != 'M' && InfoGeracao->TipoDeModelo != 'N'){
        free(InfoGeracao);
        return NULL;
    }
    if(debug){
        printf("%c\n", InfoGeracao->TipoDeModelo);
    }

    InfoGeracao->MatrizTabuleiro = (char**) malloc(sizeof(char*)* InfoGeracao->Linhas);
    for(int i = 0; i < InfoGeracao->Linhas; i++){
        InfoGeracao->MatrizTabuleiro[i] = (char*) malloc(sizeof (char)* InfoGeracao->Colunas);
    }
    if(debug){
        printf("%d %d\n", InfoGeracao->Linhas, InfoGeracao->Colunas);
    }

    return InfoGeracao;
}

void PreencheMatriz(Dados* NovosDados){
    for(int i = 0; i < NovosDados->Linhas; i++){
        for(int j = 0; j < NovosDados->Colunas; j++){
           scanf(" %c", &NovosDados->MatrizTabuleiro[i][j]);
        }
        getchar();
    }

}
void ImprimeMatriz(Dados* NovosDados){
    for(int i = 0; i < NovosDados->Linhas; i++){
        for(int j = 0; j < NovosDados->Colunas; j++){
            printf("%c", NovosDados->MatrizTabuleiro[i][j]);
        }
        printf("\n");
    }
}

int ModeloMoore(Dados* Moore, int linha, int coluna){
    char** Matriz = Moore->MatrizTabuleiro;
    int QuantidadeDeVizinhos = 0;

        if(Matriz[(linha+1)%Moore->Linhas][(coluna+1)%Moore->Colunas] == 'x'){
        QuantidadeDeVizinhos++;
        }
        if(Matriz[(linha-1 + Moore->Linhas)%Moore->Linhas][(coluna-1 + Moore->Colunas)%Moore->Colunas] == 'x'){
            QuantidadeDeVizinhos++;
        }
        if(Matriz[(linha-1 + Moore->Linhas)%Moore->Linhas][(coluna+1)%Moore->Colunas] == 'x'){
            QuantidadeDeVizinhos++;
        }
        if(Matriz[(linha+1)%Moore->Linhas][(coluna-1 + Moore->Colunas)%Moore->Colunas] == 'x'){
            QuantidadeDeVizinhos++;
        }
        if(Matriz[(linha+1)%Moore->Linhas][coluna] == 'x'){
            QuantidadeDeVizinhos++;
        }
        if(Matriz[linha][(coluna+1)%Moore->Colunas] == 'x'){
            QuantidadeDeVizinhos++;
        }
        if(Matriz[(linha-1 + Moore->Linhas)%Moore->Linhas][coluna] == 'x'){
            QuantidadeDeVizinhos++;
        }
        if(Matriz[linha][(coluna-1 + Moore->Colunas)%Moore->Colunas] == 'x'){
            QuantidadeDeVizinhos++;
        }
    return QuantidadeDeVizinhos;
}


int ModeloNeumann(Dados* Neumann, int linha, int coluna){
   char** Matriz = Neumann->MatrizTabuleiro;
    int QuantidadeDeVizinhos = 0;

    if(Matriz[(linha+1)%Neumann->Linhas][coluna] == 'x'){
        QuantidadeDeVizinhos++;
    }
    if(Matriz[linha][(coluna+1)%Neumann->Colunas] == 'x'){
        QuantidadeDeVizinhos++;
    }
    if(Matriz[(linha-1 + Neumann->Linhas)%Neumann->Linhas][coluna] == 'x'){
        QuantidadeDeVizinhos++;
    }
    if(Matriz[linha][(coluna-1 + Neumann->Colunas)%Neumann->Colunas] == 'x'){
        QuantidadeDeVizinhos++;
    }
    if(Matriz[(linha+2)%Neumann->Linhas][coluna] == 'x'){
        QuantidadeDeVizinhos++;
    }
    if(Matriz[linha][(coluna+2)%Neumann->Colunas] == 'x'){
        QuantidadeDeVizinhos++;
    }
    if(Matriz[linha][(coluna-2 + Neumann->Colunas)%Neumann->Colunas] == 'x'){
        QuantidadeDeVizinhos++;
    }
    if(Matriz[(linha-2 + Neumann->Linhas)%Neumann->Linhas][coluna] == 'x'){
        QuantidadeDeVizinhos++;
    }
    return QuantidadeDeVizinhos;
}
