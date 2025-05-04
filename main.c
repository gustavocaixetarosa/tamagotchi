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
    int horas_doente;
    bool doente;
    char nome[20];
} Tamagotchi;

Tamagotchi novoTamagotchi(char nome[]) {
    Tamagotchi t;
    t.tempo_de_vida_em_horas = 0;
    t.felicidade = 5;
    t.limpeza = 10;
    t.fome = 0;
    t.horas_doente = 0;
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
const char* estaDoente(bool doente);
void jogar(Tamagotchi* tamagotchi);
void lidarComDoenca(Tamagotchi* tamagotchi);
void morrer(Tamagotchi* defunto, char* causa);
void mostrarMenu();
int venceuPartida(int arma);
void verStatus(Tamagotchi* tamagotchi);
void verificarStatus(Tamagotchi* tamagotchi);

int main() {
    char nomeEscolhido[20];
    printf("Qual o nome desejado para seu novo bichinho? ");
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
        printf("%s nao esta com fome. Ficou triste!\n", tamagotchi->nome);
        alterarFelicidade(tamagotchi, -2);
    } else if(tamagotchi->fome > 4){
        alterarFome(tamagotchi, -4);
        alterarFelicidade(tamagotchi, 2);
        printf("%s foi alimentado!\n", tamagotchi->nome);
    } else {
        tamagotchi->fome = ATRIB_MIN;
        alterarFelicidade(tamagotchi, 2);
        printf("%s foi alimentado!\n", tamagotchi->nome);
    }
}

void alterarFelicidade(Tamagotchi *tamagotchi, int valor) {
    tamagotchi->felicidade += valor;
    if (tamagotchi->felicidade < ATRIB_MIN) tamagotchi->felicidade = ATRIB_MIN;
    if (tamagotchi->felicidade > ATRIB_MAX) tamagotchi->felicidade = ATRIB_MAX;
}

void alterarFome(Tamagotchi *tamagotchi, int valor) {
    tamagotchi->fome += valor;
    if (tamagotchi->fome < ATRIB_MIN) tamagotchi->fome = ATRIB_MIN;
    if (tamagotchi->fome > ATRIB_MAX) tamagotchi->fome = ATRIB_MAX;
}

void alterarLimpeza(Tamagotchi *tamagotchi, int valor) {
    tamagotchi->limpeza += valor;
    if (tamagotchi->limpeza < ATRIB_MIN) tamagotchi->limpeza = ATRIB_MIN;
    if (tamagotchi->limpeza > ATRIB_MAX) tamagotchi->limpeza = ATRIB_MAX;
}

void avancarTempo(Tamagotchi* tamagotchi){
    verificarStatus(tamagotchi);
    tamagotchi->tempo_de_vida_em_horas += 8;
    alterarFelicidade(tamagotchi, -3);
    alterarLimpeza(tamagotchi, -2);
    alterarFome(tamagotchi, 2);
    lidarComDoenca(tamagotchi);
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
    printf("%s tomou um banho refrescante!\n", tamagotchi->nome);
    tamagotchi->limpeza = ATRIB_MAX;
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

void lidarComDoenca(Tamagotchi* tamagotchi){
    srand(time(NULL));
    int cura_aleatoria = rand() % 3, doenca_aleatoria = rand() % 2;

    if(tamagotchi->doente){
        if(tamagotchi->horas_doente == 8){
            if(cura_aleatoria == 0){
                printf("\nWow! %s esta curado!! E um milagre.\n", tamagotchi->nome);
                tamagotchi->doente = false;
            } 
        } else if(tamagotchi->horas_doente == 16){
            if(cura_aleatoria != 0){
                printf("\nWow! %s esta curado!! Ja era hora...\n", tamagotchi->nome);
                tamagotchi->doente = false;
            }
        } else if(tamagotchi->horas_doente == 24){
            printf("\nWow! %s esta curado!!\n", tamagotchi->nome);
            tamagotchi->doente = false;
        }

        if(tamagotchi->doente){
            tamagotchi->horas_doente += 8;
            printf("%s continua dodoi. Pobre coitado!\n", tamagotchi->nome);
        }
    } else {
        if(doenca_aleatoria == 0){
            tamagotchi->doente = true;
            printf("Vish, %s pegou uma gripe! %d Melhor dar uma atencao especial a ele.\n", tamagotchi->nome);
        }
    }
}

void morrer(Tamagotchi* defunto, char* causa){
    if(strcmp(causa, "fome") == 0){
        printf("Morreu de fome!!!\n");
    } else if(strcmp(causa, "infelicidade") == 0){
        printf("Nao tratou bem seu amigo e ele morreu de infelicidade! Voce e um monstro o.O\n");
    } else if(strcmp(causa, "sujeira") == 0){
        printf("Morreu de sujo! X|\n");
    }
    printf("Descanse em paz, %s.\nSeus %d longos dias de vida foram incriveis. Nunca te esqueceremos...", defunto->nome, defunto->tempo_de_vida_em_horas / 24);
    desligar();

    exit(0);
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
    printf(" %s :    Tempo de vida: %d dias\nFelicidade: %d\nFome: %d\nLimpeza: %d\nDoente: %s\n", 
           tamagotchi->nome, 
           tamagotchi->tempo_de_vida_em_horas / 24, 
           tamagotchi->felicidade, 
           tamagotchi->fome, 
           tamagotchi->limpeza, 
           estaDoente(tamagotchi->doente));
}

void verificarStatus(Tamagotchi* tamagotchi){
    if(tamagotchi->limpeza == 0){
        morrer(tamagotchi, "sujeira");
    }  else if (tamagotchi->limpeza <= 2){
        printf("%s vai morrer de sujeira!!!\n", tamagotchi->nome);
    } else if (tamagotchi->limpeza < 5){
        printf("%s precisa de um banho!\n", tamagotchi->nome);
    }

    if(tamagotchi->fome == 10){
        morrer(tamagotchi, "fome");
    } else if(tamagotchi->fome  >= 8){
        printf("%s ta morrendo de fome, tadinho...\n", tamagotchi->nome);
    } else if(tamagotchi->fome > 5){
        printf("%s ta amarrado no pau. Nem lembra a ultima vez que comeu!\n", tamagotchi->nome);
    }

    if(tamagotchi->felicidade == 0){
        morrer(tamagotchi, "infelicidade");
    } else if(tamagotchi->felicidade <= 3){
        printf("O %s ta bem infeliz. Da pra dar uma atencao???\n", tamagotchi->nome);
    } else if(tamagotchi->felicidade < 6){
        printf("%s nao tem motivos pra ficar feliz...\n", tamagotchi->nome);
    }

    if(tamagotchi->tempo_de_vida_em_horas == TEMPO_MAXIMO){
        printf("\n✨✨ PARABÉNS! ✨✨\n");
        printf("Seu Tamagotchi viveu uma vida plena e feliz por 7 dias!\n");
        printf("Ele se tornou uma lenda entre os bichinhos virtuais...\n");
        printf("🐾 Obrigado por cuidar tão bem dele! 🐾\n");
        printf("\nNo último suspiro, ele sorri para você e sussurra:\n");
        printf("\"Obrigado por tudo, meu amigo... 💖\"\n");
        printf("\n🏆 VOCÊ VENCEU O JOGO! 🏆\n");
        desligar();
    }

}
