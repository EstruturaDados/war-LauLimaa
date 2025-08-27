#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// definição da estrutura para um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//tipos das funções
void exibirTerritorios(Territorio* mapa, int numTerritorios);
void cadastrarTerritorios(Territorio* mapa, int numTerritorios);
void atacar(Territorio* atacante, Territorio* defensor);
bool verificarVitoria(Territorio* mapa, int numTerritorios);
void liberarMemoria(Territorio* mapa);

int main() {
    int numTerritorios;
    int atacante_idx, defensor_idx;
    char continuar_ataque;

    srand(time(NULL));

    printf("--- WAR Estruturado: Nivel Avancado ---\n");
    printf("Quantos territorios voce deseja cadastrar? ");
    scanf("%d", &numTerritorios);

    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, numTerritorios);

    printf("\n--- Territorios Cadastrados ---\n");
    exibirTerritorios(mapa, numTerritorios);

    // loop de turno completo
    while(true) {
        printf("\n--- Novo Turno ---\n");
        do {
            printf("\n--- Turno de Ataque ---\n");
            printf("Escolha o atacante (1 a %d): ", numTerritorios);
            scanf("%d", &atacante_idx);

            printf("Escolha o defensor (1 a %d): ", numTerritorios);
            scanf("%d", &defensor_idx);
            
            if (atacante_idx < 1 || atacante_idx > numTerritorios ||
                defensor_idx < 1 || defensor_idx > numTerritorios) {
                printf("Escolha invalida.\n");
                continue;
            }

            Territorio* atacante = &mapa[atacante_idx - 1];
            Territorio* defensor = &mapa[defensor_idx - 1];

            if (atacante == defensor) {
                printf("Nao pode atacar a si mesmo.\n");
                continue;
            }

            if (strcmp(atacante->cor, defensor->cor) == 0) {
                printf("Nao pode atacar um territorio da mesma cor.\n");
                continue;
            }

            if (atacante->tropas <= 1) {
                printf("Ataque com menos de 2 tropas nao e possivel.\n");
                continue;
            }

            atacar(atacante, defensor);

            printf("\n--- Mapa Atualizado ---\n");
            exibirTerritorios(mapa, numTerritorios);
            
            // verifica a vitória após cada ataque
            if (verificarVitoria(mapa, numTerritorios)) {
                // se alguém venceu, encerra o jogo
                goto fim_jogo;
            }

            printf("\nDeseja continuar atacando neste turno? (s/n): ");
            scanf(" %c", &continuar_ataque);
            
        } while (continuar_ataque == 's' || continuar_ataque == 'S');
    }
    
fim_jogo:
    printf("\nJogo terminado! Parabens ao vencedor!\n");
    liberarMemoria(mapa);
    
    return 0;
}

//funções de apoio
void cadastrarTerritorios(Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor: ");
        scanf("%s", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirTerritorios(Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("Territorio %d: %s (%s) - %d tropas\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) ataca %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("Dados: Atacante (%d) vs Defensor (%d)\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante vence!\n");
        strcpy(defensor->cor, atacante->cor);
        
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("Ataque perdeu.\n");
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
    }
}

//função para verificar se um jogador venceu
bool verificarVitoria(Territorio* mapa, int numTerritorios) {
    if (numTerritorios <= 1) {
        return false; // Não temjogo para um ou menos territórios
    }
    
    char corVencedora[10];
    strcpy(corVencedora, mapa[0].cor);
    
    // verifica se tem mesma cor
    for (int i = 1; i < numTerritorios; i++) {
        if (strcmp(mapa[i].cor, corVencedora) != 0) {
            // Se encontrar uma cor diferente, vitória nao é definida
            return false;
        }
    }
    
    // Se o loop terminou e todas as cores são iguais, alguém venceu
    printf("\nParabens! O jogador da cor '%s' conquistou todos os territorios!\n", corVencedora);
    return true;
}

//função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada.\n");
}
