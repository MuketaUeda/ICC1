#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int duracao;
    char* nomeMusica;
    char* Artista;
}Musica;

typedef struct{
    Musica* musica[15];
    char* nomePlaylist;
    int tamanhoPlaylist;
    int tocandoAgora;
}Playlist;

char *LeStrings();
void proximaMusica(Playlist*);
void musicaAnterior(Playlist*);
void escreverCabecalho(Playlist *pl, FILE *arquivo);
void escreverPlaylist(Musica *m, FILE *arquivo);
void lerCabecalho(Playlist *pl, FILE *arquivo);
Musica *lerPlaylist(FILE *arquivo);
FILE* abrirLeitura(char *nomeArquivo);
FILE* abrirEscrita(char *nomeArquivo);
void binaryToNum(char *binFilename);

int main(){

    int comando;
    //alocando dinamicamente os dados da playlist
    Playlist* NovaPlaylist;
    NovaPlaylist = (Playlist*) malloc(sizeof(Playlist));

    char *nomeBin = NULL;
    FILE *arquivo = NULL;

    //inicializando variaveis
    NovaPlaylist->tocandoAgora = 0;
    NovaPlaylist->tamanhoPlaylist = 0;
    NovaPlaylist->nomePlaylist = LeStrings();
    do{
        scanf("%d ", &comando);
        fflush(stdin);
        switch(comando){

            //adiciona uma nova musica a playlist
            case 1:
                if(NovaPlaylist->tamanhoPlaylist == 15){
                    printf("Playlist cheia!\n");
                    continue;
                }
                NovaPlaylist->musica[NovaPlaylist->tamanhoPlaylist] = (Musica*) malloc(sizeof (Musica));
                NovaPlaylist->musica[NovaPlaylist->tamanhoPlaylist]->nomeMusica = LeStrings();
                NovaPlaylist->musica[NovaPlaylist->tamanhoPlaylist]->Artista = LeStrings();
                scanf("%d", &NovaPlaylist->musica[NovaPlaylist->tamanhoPlaylist]->duracao);
                printf("Musica %s de %s adicionada com sucesso.\n", NovaPlaylist->musica[NovaPlaylist->tamanhoPlaylist]->nomeMusica,
                NovaPlaylist->musica[NovaPlaylist->tamanhoPlaylist]->Artista);
                NovaPlaylist->tamanhoPlaylist++;
                break;

            //exibi na tela todas as musicas que estao contidas na playlist
            case 2:
                printf("---- Playlist: %s ----\n", NovaPlaylist->nomePlaylist);
                printf("Total de musicas: %d\n", NovaPlaylist->tamanhoPlaylist);
                for(int i = 0; i < NovaPlaylist->tamanhoPlaylist; i++) {
                    printf("\n");
                    if(i == NovaPlaylist->tocandoAgora) {
                        printf("=== NOW PLAYING ===\n");
                    }
                    printf("(%d). '%s'\n", i+1, NovaPlaylist->musica[i]->nomeMusica);
                    printf("Artista: %s\n", NovaPlaylist->musica[i]->Artista);
                    printf("Duracao: %d segundos\n", NovaPlaylist->musica[i]->duracao);
                }
                printf("\n");
                break;

            //avanca para a proxima musica
            case 3:
                proximaMusica(NovaPlaylist);
                break;

            //volta para a musica anterior
            case 4:
                musicaAnterior(NovaPlaylist);
                break;

            case 5:
            //Pega a playlist da Ram e salva em um arquivo
                nomeBin = LeStrings();
                arquivo = abrirEscrita(nomeBin);

                escreverCabecalho(NovaPlaylist, arquivo);

                for(int i = 0; i < NovaPlaylist->tamanhoPlaylist; i++){
                    escreverPlaylist(NovaPlaylist->musica[i], arquivo);
                }
                printf("Playlist %s salva com sucesso.\n", nomeBin);

                fclose(arquivo);
                binaryToNum(nomeBin);

                break;
            //Pega a playlist do arquivo e passa para a RAM
           case 6:
                // desalocando musicas anteriores e nome da playlist
                for(int i = 0; i < NovaPlaylist->tamanhoPlaylist; i++){
                    free(NovaPlaylist->musica[i]->Artista);
                    free(NovaPlaylist->musica[i]->nomeMusica);
                    free(NovaPlaylist->musica[i]);
                }
                free(NovaPlaylist->nomePlaylist);

                nomeBin = LeStrings();
                arquivo = abrirLeitura(nomeBin);
                lerCabecalho(NovaPlaylist, arquivo);

                for(int i = 0; i < NovaPlaylist->tamanhoPlaylist; i++){
                    NovaPlaylist->musica[i] = lerPlaylist(arquivo); // atribui a musica lida do arquivo
                }

                printf("Playlist %s carregada com sucesso.\n", nomeBin);

                fclose(arquivo);
                binaryToNum(nomeBin);

                break;

            default:
                break;
        }
    }while(comando != 7);
    //desalocando memoria
    for(int i = 0; i < NovaPlaylist->tamanhoPlaylist; i++){
        free(NovaPlaylist->musica[i]->Artista);
        free(NovaPlaylist->musica[i]->nomeMusica);
        free(NovaPlaylist->musica[i]);
    }
    free(NovaPlaylist->nomePlaylist);
    free(NovaPlaylist);
    free(nomeBin);

    return 0;
}

//Escreve escreve o nome da nova playlist no arquivo binario
void escreverCabecalho(Playlist *pl, FILE *arquivo){
    int tamNomePl = strlen(pl->nomePlaylist);

    fwrite(&tamNomePl, sizeof(int), 1, arquivo);
    fwrite(pl->nomePlaylist, sizeof(char), tamNomePl, arquivo);
    fwrite(&pl->tamanhoPlaylist, sizeof(int), 1, arquivo);
}

//Escreve uma musica no arquivo binario
void escreverPlaylist(Musica *m, FILE *arquivo){
    int tamMusica = strlen(m->nomeMusica);
    int tamArtista = strlen(m->Artista);

    fwrite(&tamMusica, sizeof(int), 1, arquivo);
    fwrite(m->nomeMusica, sizeof(char), tamMusica, arquivo);
    fwrite(&tamArtista, sizeof(int), 1, arquivo);
    fwrite(m->Artista, sizeof(char), tamArtista, arquivo);
    fwrite(&m->duracao, sizeof(int), 1, arquivo);
}

//Lê o nome da nova playlist do arquivo binario
void lerCabecalho(Playlist *pl, FILE *arquivo){
    int tamNomePl = 0;

    fread(&tamNomePl, sizeof(int), 1, arquivo);
    pl->nomePlaylist = calloc(tamNomePl+1, sizeof(char));

    fread(pl->nomePlaylist, sizeof(char), tamNomePl, arquivo);
    fread(&pl->tamanhoPlaylist, sizeof(int), 1, arquivo);
}

//Lê registro de musicas no arquivo binario, retorna um struct musica
Musica *lerPlaylist(FILE *arquivo){
    int tamMusica = 0, tamArtista = 0;
    Musica *m = malloc(sizeof(Musica));

    fread(&tamMusica, sizeof(int), 1, arquivo);
    m->nomeMusica = calloc(tamMusica+1, sizeof(char));
    fread(m->nomeMusica, sizeof(char), tamMusica, arquivo);
    fread(&tamArtista, sizeof(int), 1, arquivo);
    m->Artista = calloc(tamMusica+1, sizeof(char));
    fread(m->Artista, sizeof(char), tamArtista, arquivo);
    fread(&m->duracao, sizeof(int), 1, arquivo);

    return m;
}

char *LeStrings(){
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


void proximaMusica(Playlist* PlaylistAtual){
    if(PlaylistAtual->tamanhoPlaylist == 0){
        return;
    }
    if(PlaylistAtual->tocandoAgora == PlaylistAtual->tamanhoPlaylist){
        PlaylistAtual->tocandoAgora = 0;
        return;
    }
    PlaylistAtual->tocandoAgora++;
}

void musicaAnterior(Playlist* PlaylistAtual){
    if(PlaylistAtual->tamanhoPlaylist == 0){
        return;
    }
    if(PlaylistAtual->tocandoAgora == 0){
        PlaylistAtual->tocandoAgora = 15;
        return;
    }
    PlaylistAtual->tocandoAgora--;
}

//Abrir o arquivo em binario para ler
FILE* abrirLeitura(char *nomeArquivo){
    FILE *fb;

    if ((fb = fopen(nomeArquivo, "rb")) == NULL){
        printf("Arquivo %s nao existe.\n", nomeArquivo), exit(0);
    }

    return fb;
}

//Abrir o arquivo em binario para escrever
FILE* abrirEscrita(char *nomeArquivo){
    FILE *fb;

    if ((fb = fopen(nomeArquivo, "wb")) == NULL){
        printf("Arquivo %s nao existe.\n", nomeArquivo), exit(0);
    }

    return fb;
}

void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}
