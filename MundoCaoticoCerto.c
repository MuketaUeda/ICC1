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
    //Chamando funcao de alocacao de dados e leitura
    Dados* NovosDados = AlocaDados();
    if(NovosDados == NULL){
        printf("Dados de entrada apresentam erro.");
        return 0;
    }
    //Chamando o funcao de preenchimento da matriz
    PreencheMatriz(NovosDados);
    //Matriz auxiliar, para salvar a geracao correta e comparar corretamente os vizinhos
    char** MatrizAuxiliar = NULL;
    MatrizAuxiliar = malloc(NovosDados->Linhas * sizeof(char*));
    for(int i = 0; i < NovosDados->Linhas; i++){
        MatrizAuxiliar[i] = malloc(NovosDados->Colunas * sizeof(char));
    }
    //Moore
    if(NovosDados->TipoDeModelo == 'M'){
        for(int k = 0; k < NovosDados->NumeroGeracoes; k++){
            for(int i = 0; i < NovosDados->Linhas; i++){
                for(int j = 0; j < NovosDados->Colunas; j++){
                    Vizinhos = ModeloMoore(NovosDados, i, j);
                    if(NovosDados->MatrizTabuleiro[i][j] == 'x'){
                        if(Vizinhos < 2 || Vizinhos > 3){
                            MatrizAuxiliar[i][j] = '.';
                        }
                    }
                    if(NovosDados->MatrizTabuleiro[i][j] == '.'){
                        if(Vizinhos == 3){
                            MatrizAuxiliar[i][j] = 'x';
                        }
                    }
                }
            }
            //Loop para copia dos dados da matriz auxiliar para a principal
            for(int i = 0; i < NovosDados->Linhas; i++) {
                for(int j = 0; j < NovosDados->Colunas; j++) {
                    NovosDados->MatrizTabuleiro[i][j] = MatrizAuxiliar[i][j];

                }
            }

        }
        ImprimeMatriz(NovosDados);

    }
    //Neumann
    if(NovosDados->TipoDeModelo == 'N'){
        for(int k = 0; k < NovosDados->NumeroGeracoes; k++){
            for(int i = 0; i < NovosDados->Linhas; i++){
                for(int j = 0; j < NovosDados->Colunas; j++){
                    Vizinhos = ModeloNeumann(NovosDados, i, j);
                    if(NovosDados->MatrizTabuleiro[i][j] == 'x'){
                        if(Vizinhos < 2 || Vizinhos > 3){
                            MatrizAuxiliar[i][j] = '.';
                            continue;
                        }
                        else{
                            MatrizAuxiliar[i][j] = 'x';
                            continue;
                        }
                    }
                    if(NovosDados->MatrizTabuleiro[i][j] == '.'){
                        if(Vizinhos == 3){
                            MatrizAuxiliar[i][j] = 'x';
                            continue;
                        }
                        else{
                            MatrizAuxiliar[i][j] = '.';
                        }
                    }
                }
            }
            //Loop para copia dos dados da matriz auxiliar para a principal
            for(int i = 0; i < NovosDados->Linhas; i++) {
                for(int j = 0; j < NovosDados->Colunas; j++) {
                    NovosDados->MatrizTabuleiro[i][j] = MatrizAuxiliar[i][j];

                }
            }

        }
        ImprimeMatriz(NovosDados);

    }
    //desalocando memoria
    for(int i = 0; i < NovosDados->Linhas; i++) {
        free(NovosDados->MatrizTabuleiro[i]);
    }
    for(int i = 0; i < NovosDados->Linhas; i++){
        free(MatrizAuxiliar[i]);
    }
    free(MatrizAuxiliar);
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
//funcao de preenchimento de matriz tratando o \n ter todos os espacos corretos
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

        //Casos generalizados de virificacao de vizinhanca e matriz redonda
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

    //Casos generalizados de virificacao de vizinhanca e matriz redonda
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
