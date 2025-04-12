#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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


void alimentar(Tamagotchi tamagotchi);

void alterarFelicidade(Tamagotchi tamagotchi, int valor);

void alterarFome(Tamagotchi tamagotchi, int valor);

void avancarNoTempo(Tamagotchi tamagotchi);

void mostrarMenu();

void jogar(Tamagotchi tamagotchi);

void darBanho(Tamagotchi tamagotchi);

int venceuPartida(int arma);

void verificarStatus(Tamagotchi tamagotchi);

int main(){
    int opcao;
    char nomeEscolhido[20];
    printf("Qual o nome desejada para seu novo bichinho?: ");
    scanf("%c ", &nomeEscolhido);

    Tamagotchi t1 = novoTamagotchi(nomeEscolhido);    
    int escolha_menu = 0;

    do{
        mostrarMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (escolha_menu)
        {
        case 1:
            avancarTempo(t1);
            break;
        case 2:
            alimentar(t1);
            break;
        case 3:
            jogar(t1);
            break;
        case 4:
            darBanho(t1);
            break;
        case 5:
            verStatus(t1);
            break;
        case 6:
            desligar(t1);
            break;
        default:
            desligar(t1);
            break;
        }
    } while(escolha_menu != 6);

    return 0;
}


void alimentar(Tamagotchi tamagotchi){
    if(tamagotchi.fome == ATRIB_MIN){
        printf("%c não está com fome. Ficou titi!", tamagotchi.nome);
        alterarFelicidade(tamagotchi, -2);
    } else if(tamagotchi.fome > 4){
        alterarFome(tamagotchi, -4);
    } else {
        tamagotchi.fome = ATRIB_MIN;
    }
}

void alterarFome(Tamagotchi tamagotchi, int valor){
    
}

void avancarTempo(Tamagotchi tamagotchi){
    verificarStatus(tamagotchi);
    tamagotchi.tempo_de_vida_em_horas += 8;
    alterarFelicidade(tamagotchi, -2);
    tamagotchi.felicidade -= 3; 
}
void darBanho(Tamagotchi tamagotchi){
    if(tamagotchi.limpeza == ATRIB_MAX){
        printf("%c já estava limpo. Que maldade!\n", tamagotchi.nome);
        alterarFelicidade(tamagotchi, -6);
        return;
    }
    tamagotchi.limpeza = ATRIB_MAX;
    alterarFelicidade(tamagotchi, 5);
}

void jogar(Tamagotchi tamagotchi){
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
        printf("%c venceu!\n", tamagotchi.nome);
        alterarFelicidade(tamagotchi, 5);
    } else{
        printf("Empate!\n");
    }
}

void mostrarMenu() {
    printf("1. Avançar o tempo\n");
    printf("2. Alimentar\n");
    printf("3. Jogar\n");
    printf("4. Dar banho\n");
    printf("5. Ver status\n");
    printf("6. Desligar\n");
}

int venceuPartida(int arma) {
    int armaDoPet = rand() % 3;

    printf("Sua arma: %d\n", arma);
    printf("Arma do pet: %d\n", armaDoPet);

    if(arma == armaDoPet) {
        return 0;
    } else if((arma == 0 && armaDoPet == 2) || 
              (arma == 1 && armaDoPet == 0) || 
              (arma == 2 && armaDoPet == 1)) {
        return 1;
    } else {
        return 2;
    }
}

void verificarStatus(Tamagotchi tamagotchi){
    if (tamagotchi.limpeza < 2){
        printf("%c vai morrer de sujeira!!!", tamagotchi.nome);
    } 

    if(tamagotchi.fome < 1){
        printf("%c vai morrer de fome!!!", tamagotchi.nome);
    }
}


