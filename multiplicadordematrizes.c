#include <stdio.h>
#include <stdlib.h>

int main(){

    int num_linhasA, num_colunasA;
    int num_linhasB, num_colunasB;

    scanf("%d %d", &num_linhasA, &num_colunasA);
    scanf("%d %d", &num_linhasB, &num_colunasB);

    if(num_linhasA < 0 && num_colunasA < 0 && num_linhasB < 0 && num_colunasB < 0){
        printf("Valores invalidos para a multiplicacao.\n");
    }
    int matrizA[num_linhasA][num_colunasA], matrizB[num_linhasB][num_colunasB], matrizC[num_linhasA][num_colunasB];
    int semente;
    scanf("%d", &semente);
    srand(semente);

        if(num_colunasA == num_linhasB){
        for(int i = 0; i < num_linhasA; i++){
            for(int j = 0; j < num_colunasA; j++){
            matrizA[i][j] = rand()%50 - 25;
            }
        }
        for(int i = 0; i < num_linhasB; i++){
            for(int j = 0; j < num_colunasB; j++){
            matrizB[i][j] = rand()%50 - 25;
            }
        }

    int aux;
        for(int Lin_atual = 0; Lin_atual < num_linhasA; Lin_atual++){
            for(int Colun_atual = 0; Colun_atual < num_colunasB; Colun_atual++){
            aux = 0;
                for(int i = 0; i < num_linhasB; i++){
                aux += matrizA[Lin_atual][i] * matrizB[i][Colun_atual];
                }
            matrizC[Lin_atual][Colun_atual] = aux;
            }

        }
        for(int i = 0; i < num_linhasA; i++){
        printf("Linha %d: ", i);
        for(int j = 0; j < num_colunasB; j++){
            printf("%d ", matrizC[i][j]);
        }
        printf("\n");
        }
    }
    else{
        printf("Valores invalidos para a multiplicacao.\n");
    }

    return 0;

}
