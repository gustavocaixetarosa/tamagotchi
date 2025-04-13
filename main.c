#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEMPO_MAXIMO 168
#define ATRIB_MAX 10
#define ATRIB_MIN 0

typedef struct {
    int tempo_de_vida_em_horas;
    int felicidade;
    int limpeza;
    int fome;
    bool doente;
    char nome[20];
} Tamagotchi;

Tamagotchi novoTamagotchi(char nome[]) {
    Tamagotchi t;
    t.tempo_de_vida_em_horas = 0;
    t.felicidade = 5;
    t.limpeza = 10;
    t.fome = 0;
    t.doente = false;
    strcpy(t.nome, nome);
    return t;
}

void alimentar(Tamagotchi* tamagotchi);
void alterarFelicidade(Tamagotchi* tamagotchi, int valor);
void alterarFome(Tamagotchi* tamagotchi, int valor);
void avancarTempo(Tamagotchi* tamagotchi);
void darBanho(Tamagotchi* tamagotchi);
void desligar();
void jogar(Tamagotchi* tamagotchi);
void mostrarMenu();
int venceuPartida(int arma);
void verStatus(Tamagotchi* tamagotchi);
void verificarStatus(Tamagotchi* tamagotchi);
const char* estaDoente(bool doente);

int main() {
    char nomeEscolhido[20];
    printf("Qual o nome desejado para seu novo bichinho?: ");
    scanf("%s", nomeEscolhido);

    Tamagotchi t1 = novoTamagotchi(nomeEscolhido);    
    int opcao = 0;

    do {
        mostrarMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                avancarTempo(&t1);
                break;
            case 2:
                alimentar(&t1);
                break;
            case 3:
                jogar(&t1);
                break;
            case 4:
                darBanho(&t1);
                break;
            case 5:
                verStatus(&t1);
                break;
            case 6:
                desligar();
                break;
            default:
                desligar();
                break;
        }
    } while (opcao != 6);

    return 0;
}

void alimentar(Tamagotchi* tamagotchi) {
    if(tamagotchi->fome == ATRIB_MIN){
        printf("%s nao esta com fome. Ficou titi!\n", tamagotchi->nome);
        alterarFelicidade(tamagotchi, -2);
    } else if(tamagotchi->fome > 4){
        alterarFome(tamagotchi, -4);
    } else {
        tamagotchi->fome = ATRIB_MIN;
    }
}

void alterarFelicidade(Tamagotchi* tamagotchi, int valor){
    if(tamagotchi->felicidade + valor > ATRIB_MAX){
        tamagotchi->felicidade = ATRIB_MAX;
    } else if(tamagotchi->felicidade + valor < ATRIB_MIN){
        tamagotchi->felicidade = ATRIB_MIN;
    } else {
        tamagotchi->felicidade += valor;
    }
}

void alterarFome(Tamagotchi* tamagotchi, int valor){
    if(tamagotchi->fome + valor > ATRIB_MAX){
        tamagotchi->fome = ATRIB_MAX;
    } else if(tamagotchi->fome + valor < ATRIB_MIN){
        tamagotchi->fome = ATRIB_MIN;
    } else {
        tamagotchi->fome += valor;
    }
}

void avancarTempo(Tamagotchi* tamagotchi){
    verificarStatus(tamagotchi);
    tamagotchi->tempo_de_vida_em_horas += 8;
    alterarFelicidade(tamagotchi, -2);
}

void desligar(){
    printf("Tamagotchi desligado. Até mais!\n");
}

void darBanho(Tamagotchi* tamagotchi){
    if(tamagotchi->limpeza == ATRIB_MAX){
        printf("%s já estava limpo. Que maldade!\n", tamagotchi->nome);
        alterarFelicidade(tamagotchi, -6);
        return;
    }
    tamagotchi->limpeza = ATRIB_MAX;
    alterarFelicidade(tamagotchi, 5);
}

const char* estaDoente(bool doente){
    return doente ? "Sim" : "Não";
}

void jogar(Tamagotchi* tamagotchi){
    int arma;
    printf(" *** PEDRA, PAPEL, TESOURA ***\n");
    printf("1. Pedra\n");
    printf("2. Papel\n");
    printf("3. Tesoura\n");
    printf("Escolha sua arma: \n");
    scanf("%d", &arma);

    int resultado = venceuPartida(arma);
    if(resultado == 1){
        printf("Você venceu!\n");
        alterarFelicidade(tamagotchi, 3);
    } else if(resultado == 2){
        printf("%s venceu!\n", tamagotchi->nome);
        alterarFelicidade(tamagotchi, 5);
    } else{
        printf("Empate!\n");
    }
}

void mostrarMenu() {
    printf("\n\n\n*** MENU ***\n");
    printf("1. Avancar o tempo\n");
    printf("2. Alimentar\n");
    printf("3. Jogar\n");
    printf("4. Dar banho\n");
    printf("5. Ver status\n");
    printf("6. Desligar\n");
}

int venceuPartida(int arma) {
    int armaDoPet = rand() % 3 + 1;

    printf("Sua arma: %d\n", arma);
    printf("Arma do pet: %d\n", armaDoPet);

    if(arma == armaDoPet) {
        return 0;
    } else if((arma == 1 && armaDoPet == 3) || 
              (arma == 2 && armaDoPet == 1) || 
              (arma == 3 && armaDoPet == 2)) {
        return 1;
    } else {
        return 2;
    }
}

void verStatus(Tamagotchi* tamagotchi){
    printf("\n *** STATUS ***\n");
    printf(" %s :    Tempo de vida: %d horas\nFelicidade: %d\nFome: %d\nLimpeza: %d\nDoente: %s\n", 
           tamagotchi->nome, 
           tamagotchi->tempo_de_vida_em_horas, 
           tamagotchi->felicidade, 
           tamagotchi->fome, 
           tamagotchi->limpeza, 
           estaDoente(tamagotchi->doente));
}

void verificarStatus(Tamagotchi* tamagotchi){
    if (tamagotchi->limpeza < 2){
        printf("%s vai morrer de sujeira!!!\n", tamagotchi->nome);
    } 

    if(tamagotchi->fome > 8){
        printf("%s vai morrer de fome!!!\n", tamagotchi->nome);
    }
}
