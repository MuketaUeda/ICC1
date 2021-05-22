#include <stdio.h>

int main(){

    char teclado[49];

    for(int i = 0; i < 49; i++){
        teclado[i] = fgetc(stdin);
        fgetc(stdin);

        if(teclado[i] == '_'){
            teclado[i] = ' ';
        }
        else if(teclado[i] == 'E'){
            teclado[i] = '\n';
        }
    }

    int num_carac;
    scanf("%d", &num_carac);

    int mensagem[num_carac];
    for(int i = 0; i < num_carac; i++){
        scanf("%d", &mensagem[i]);
        fgetc(stdin);
    }
    for(int i = 0; i < num_carac; i++){
        printf("%c", teclado[mensagem[i]]);
    }
    return 0;
}

