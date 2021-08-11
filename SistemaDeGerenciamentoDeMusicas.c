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

int main(){

    int comando;
    //alocando dinamicamente os dados da playlist
    Playlist* NovaPlaylist;
    NovaPlaylist = (Playlist*) malloc(sizeof(Playlist));
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

            //exibi na tela todas as musicas que est˜ao contidas na playlist
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

            //avança para a proxima musica
            case 3:
                proximaMusica(NovaPlaylist);
                break;

            //volta para a musica anterior
            case 4:
                musicaAnterior(NovaPlaylist);
                break;

            default:
                break;
        }
    }while(comando != 5);
    //desalocando memória
    for(int i = 0; i < NovaPlaylist->tamanhoPlaylist; i++){
        free(NovaPlaylist->musica[i]->Artista);
        free(NovaPlaylist->musica[i]->nomeMusica);
        free(NovaPlaylist->musica[i]);
    }
    free(NovaPlaylist->nomePlaylist);
    free(NovaPlaylist);

    return 0;
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
