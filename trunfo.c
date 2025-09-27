#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[30];
    int forca;
    int vida;
} Carta;

// Função para sortear a carta do jogador
Carta sortearCarta() {
    int chance = rand() % 100;
    Carta c;

    if (chance < 5) { // 5% Dragão
        snprintf(c.nome, sizeof(c.nome), "Dragao (Lendario)");
        c.forca = 100;
    } else if (chance < 15) { // 10% Dinossauro
        snprintf(c.nome, sizeof(c.nome), "Dinossauro (Epico)");
        c.forca = 80;
    } else if (chance < 40) { // 25% Elfo
        snprintf(c.nome, sizeof(c.nome), "Elfo (Raro)");
        c.forca = 60;
    } else if (chance < 80) { // 40% Cavaleiro
        snprintf(c.nome, sizeof(c.nome), "Cavaleiro (Comum)");
        c.forca = 50;
    } else { // 20% Mago
        snprintf(c.nome, sizeof(c.nome), "Mago (Comum)");
        c.forca = 40;
    }

    c.vida = 100;
    return c;
}

// Função de ataque
int atacar(Carta *atacante) {
    int dano = atacante->forca;
    int critico = rand() % 100;
    if (critico < 20) { // 20% chance de crítico
        printf("CRITICO! O ataque de %s foi dobrado!\n", atacante->nome);
        dano *= 2;
    }
    return dano;
}

// Função de defesa
int defender(int dano, Carta *defensor) {
    int defesa = rand() % 100;
    if (defesa < 20) { // 20% chance de defesa aprimorada
        printf("DEFESA APRIMORADA! %s reduziu muito o dano!\n", defensor->nome);
        dano /= 4; // reduz 75%
    } else {
        dano /= 2; // defesa comum reduz 50%
    }
    return dano;
}

int main() {
    srand(time(NULL));

    printf("=== CAVALEIRO DOS ZODÍACOS ===\n");

    // Sorteio das cartas dos jogadores
    Carta j1 = sortearCarta();
    Carta j2 = sortearCarta();

    printf("Jogador 1 recebeu: %s (Forca %d, Vida %d)\n", j1.nome, j1.forca, j1.vida);
    printf("Jogador 2 recebeu: %s (Forca %d, Vida %d)\n", j2.nome, j2.forca, j2.vida);

    // Sorteio de quem começa
    int turno = rand() % 2;
    printf("\nSorteando quem começa... %s inicia!\n",
           turno == 0 ? "Jogador 1" : "Jogador 2");

    // Loop da guerra até alguém vencer
    while (j1.vida > 0 && j2.vida > 0) {
        printf("\n--- Nova Rodada ---\n");

        if (turno == 0) {
            // Jogador 1
            int escolha;
            printf("Jogador 1, deseja Atacar (1) ou Defender (2)? ");
            scanf("%d", &escolha);

            if (escolha == 1) {
                int dano = atacar(&j1);
                dano = defender(dano, &j2);
                j2.vida -= dano;
                if (j2.vida < 0) j2.vida = 0;
                printf("Jogador 1 causou %d de dano em Jogador 2.\n", dano);
            } else {
                int dano = atacar(&j2);
                dano = defender(dano, &j1);
                j1.vida -= dano;
                if (j1.vida < 0) j1.vida = 0;
                printf("Jogador 2 causou %d de dano em Jogador 1.\n", dano);
            }
        } else {
            // Jogador 2
            int escolha;
            printf("Jogador 2, deseja Atacar (1) ou Defender (2)? ");
            scanf("%d", &escolha);

            if (escolha == 1) {
                int dano = atacar(&j2);
                dano = defender(dano, &j1);
                j1.vida -= dano;
                if (j1.vida < 0) j1.vida = 0;
                printf("Jogador 2 causou %d de dano em Jogador 1.\n", dano);
            } else {
                int dano = atacar(&j1);
                dano = defender(dano, &j2);
                j2.vida -= dano;
                if (j2.vida < 0) j2.vida = 0;
                printf("Jogador 1 causou %d de dano em Jogador 2.\n", dano);
            }
        }

        // Mostrar vidas
        printf("Vida Jogador 1 (%s): %d\n", j1.nome, j1.vida);
        printf("Vida Jogador 2 (%s): %d\n", j2.nome, j2.vida);

        // Passa o turno
        turno = !turno;
    }

    // Fim da guerra
    printf("\n=== FIM DA GUERRA ===\n");
    if (j1.vida > 0) {
        printf("Jogador 1 venceu com %s!\n", j1.nome);
    } else if (j2.vida > 0) {
        printf("Jogador 2 venceu com %s!\n", j2.nome);
    } else {
        // caso os dois cheguem a 0, quem deu o último golpe vence
        printf("Ambos caíram, mas o último golpe decide...\n");
        printf("%s venceu por último golpe!\n", turno == 0 ? "jogador 2" : "Jogador 1");
    }

    return 0;
}
