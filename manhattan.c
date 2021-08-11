#include <stdio.h>
#include <math.h>
#define debug 0

typedef struct{
int x, y, TipoDeTerreno;
} PontoDeEntrega;

float DistanciaEuclidiana (PontoDeEntrega Origem, PontoDeEntrega Destino){
return sqrt( pow(Destino.x - Origem.x, 2) + pow(Destino.y - Origem.y, 2) );
}
float DistanciaExterna(PontoDeEntrega Origem, PontoDeEntrega Destino){
return fabs(Destino.x - Origem.x) + fabs(Destino.y - Origem.y);
}

int main(){
    int numCoord;
    float DistTotalEuclides = 0, DistTotalHermanns = 0;
    int Parque = 0, Casa = 0, TerrenoBaldio = 0;
    //Chamando e declarando na struct
    PontoDeEntrega PontoAtual, PontoAnterior, PontoInicial;
    scanf("%d", &numCoord);

    if(numCoord <= 0){
        printf("Falha no processamento dos dados.\n");
    return 0;
    }
    else{
            float ContornoDoTerreno;
            float DiagonalDoTerreno;
            for(int i = 0; i <= numCoord; i++){
                if(i == 0){
                    scanf("%d %d %d", &PontoInicial.x, &PontoInicial.y, &PontoInicial.TipoDeTerreno);
                    if(PontoInicial.TipoDeTerreno != -1 && PontoInicial.TipoDeTerreno != 1 && PontoInicial.TipoDeTerreno != 0){
                                printf("Falha no processamento dos dados.\n");
                                return 0;
                    }
                    PontoAnterior.x = PontoInicial.x;
                    PontoAnterior.y = PontoInicial.y;
                    PontoAnterior.TipoDeTerreno = PontoInicial.TipoDeTerreno;
                }
                else{
                        if(i != numCoord){
                            scanf("%d %d %d", &PontoAtual.x, &PontoAtual.y, &PontoAtual.TipoDeTerreno);
                            if(PontoAtual.TipoDeTerreno != -1 && PontoAtual.TipoDeTerreno != 1 && PontoAtual.TipoDeTerreno != 0){
                                printf("Falha no processamento dos dados.\n");
                                return 0;
                            }
                        }
                        else{
                                PontoAtual.x = PontoInicial.x, PontoAtual.y = PontoInicial.y;}

                    if(PontoAnterior.TipoDeTerreno == 0){
                        ContornoDoTerreno = DistanciaExterna(PontoAnterior, PontoAtual);
                        DistTotalEuclides = DistTotalEuclides + ContornoDoTerreno;
                        DistTotalHermanns = DistTotalHermanns + ContornoDoTerreno;
                        Casa++;
                        if(debug){
                            printf("DistTotalEuclides = %f\n", DistTotalEuclides);
                            printf("DistTotalHermanns = %f\n", DistTotalHermanns);
                        }
                    }
                    else if(PontoAnterior.TipoDeTerreno == -1){
                        DiagonalDoTerreno = DistanciaEuclidiana(PontoAnterior, PontoAtual);
                        DistTotalEuclides = DistTotalEuclides + DiagonalDoTerreno;
                        DistTotalHermanns = DistTotalHermanns + DiagonalDoTerreno;
                        TerrenoBaldio++;
                        if(debug){
                            printf("DistTotalEuclides = %f\n", DistTotalEuclides);
                            printf("DistTotalHermanns = %f\n", DistTotalHermanns);
                        }
                    }

                    else if(PontoAnterior.TipoDeTerreno == 1){
                        DistTotalEuclides = DistTotalEuclides + DistanciaEuclidiana(PontoAnterior, PontoAtual);
                        DistTotalHermanns = DistTotalHermanns + DistanciaExterna(PontoAnterior, PontoAtual);
                        Parque++;
                        if(debug){
                            printf("DistTotalEuclides = %f\n", DistTotalEuclides);
                            printf("DistTotalHermanns = %f\n", DistTotalHermanns);
                        }
                    }
                    PontoAnterior = PontoAtual;
                }
        }
    }

    printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n", TerrenoBaldio, Casa, Parque);
    printf("A diferenca total de distancia percorrida foi de %.2f metros.\n",DistTotalHermanns - DistTotalEuclides);


    return 0;


}
