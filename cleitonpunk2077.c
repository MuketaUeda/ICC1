#include <stdio.h>

//Gabriel Tavares Brayn Rosati
//NUSP 11355831

int main(){

    int vetor[512];

    for(int i = 0; i < 512; i++){
        scanf("%d", &vetor[i]);
    }

    int linhaAtual = 0;
    int opcode = -1;
    int add1, add2, dest;
    printf("Saida do programa:\n");
    //Loop com condição de parada
    while(opcode != 0){

        opcode = vetor[linhaAtual];
        switch(opcode){
            //ADD
            case 1:
                add1 = vetor[linhaAtual + 1];
                add2 = vetor[linhaAtual + 2];
                dest = vetor[linhaAtual + 3];
                vetor[dest] = vetor[add1] + vetor[add2];
                linhaAtual = linhaAtual + 4;
                break;
            //MUL
            case 2:
                add1 = vetor[linhaAtual + 1];
                add2 = vetor[linhaAtual + 2];
                dest = vetor[linhaAtual + 3];
                vetor[dest] = vetor[add1] * vetor[add2];
                linhaAtual = linhaAtual + 4;
                break;
            //CLT
            case 3:
                add1 = vetor[linhaAtual + 1];
                add2 = vetor[linhaAtual + 2];
                dest = vetor[linhaAtual + 3];
                if(vetor[add1] < vetor[add2]){
                    vetor[dest] = 1;
                }
                else{
                    vetor[dest] = 0;
                }
                linhaAtual = linhaAtual + 4;
                break;
            //CEQ
            case 4:
                add1 = vetor[linhaAtual + 1];
                add2 = vetor[linhaAtual + 2];
                dest = vetor[linhaAtual + 3];
                if(vetor[add1] == vetor[add2]){
                    vetor[dest] = 1;
                }
                else{
                    vetor[dest] = 0;
                }
                linhaAtual = linhaAtual + 4;
                break;
            //Jump
            case 5:
                add1 = vetor[linhaAtual + 1];
                linhaAtual =  vetor[add1];
                break;
            //JEQ
            case 6:
                add1 = vetor[linhaAtual + 1];
                add2 = vetor[linhaAtual + 2];
                if(vetor[add1] != 0){
                    linhaAtual = vetor[add2];
                }else{
                    linhaAtual = linhaAtual + 3;
                }
                break;
            //CPY
            case 7:
                add1 = vetor[linhaAtual + 1];
                dest = vetor[linhaAtual + 2];
                vetor[dest] = vetor[add1];
                linhaAtual = linhaAtual + 3;
                break;
            //PUT
            case 8:
                add1 = vetor[linhaAtual + 1];
                printf("%c", vetor[add1]);
                linhaAtual = linhaAtual + 2;
                break;
            //PTN
            case 9:
                add1 = vetor[linhaAtual + 1];
                printf("%d", vetor[add1]);
                linhaAtual = linhaAtual + 2;
                break;
            default: break;

        }
    }
    printf("\n");
    printf("Estado final da fita:\n");
    for(int i = 0; i < 512; i++){
        printf("%d\n", vetor[i]);
    }

    return 0;

}
