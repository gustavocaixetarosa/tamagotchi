#include<stdio.h>
#include<stdbool.h>

typedef struct {
    int tempo_de_vida_em_horas;
    int felicidade;
    int limpeza;
    int fome;
    bool doente;
    char nome[20];
} Tamagotchi;

bool ePar(int valor){
    if(valor % 2 == 0){
        return true;
    } else {
        return false;
    }
}

int main(){
    Tamagotchi primeiro;    

    ficarDoente(primeiro);

    if(escolha == 1){
        passarDia(primeiro);
    } if else (escolha == 2){
        alimentar(primeiro)
    }

    return 0;
}

void alimentar(Tamagotchi zezinho){
    if(zezinho.fome == 0){
        printf("%c não está com fome. Ficou titi!", zezinho.nome);
        zezinho.felicidade -= 2;
    } else if(zezinho.fome > 4){
        zezinho.fome -= 4;
    } else {
        zezinho.fome = 0;
    }
}

void passarDia(Tamagotchi zezinho){
    zezinho.fome += 2;
    zezinho.limpeza -= 3;
    zezinho.felicidade -= 3; 
    verificarStatus(zezinho);
}

void verificarStatus(Tamagotchi zezinho){
    if (zezinho.limpeza < 2){
        printf("%c vai morrer de sujeira!!!", zezinho.nome);
    } 

    if(zezinho.fome < 1){
        printf("%c vai morrer de fome!!!", zezinho.nome);
    }
}

void darBanho(Tamagotchi meuTamagotchi){
    meuTamagotchi.limpeza = 10;
    meuTamagotchi.felicidade += 5;
}

