#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// estrutura para guardar informações do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//Protótipos do ponteiro
void cadastrarTerritorios(Territorio* mapa, int numTerritorios);
void exibirTerritorios(Territorio* mapa, int numTerritorios);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int numTerritorios;
    int atacante_idx, defensor_idx;

    // rolagem de dados aleatória
    srand(time(NULL));

    // pegunta de quantos territórios deseja
    printf("Quantos territorios voce deseja cadastrar? ");
    scanf("%d", &numTerritorios);

    // Aloca a memória de acordo com a escolha
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // preenche os dados dos territórios.
    cadastrarTerritorios(mapa, numTerritorios);

    printf("\n--- Territorios Cadastrados ---\n");
    exibirTerritorios(mapa, numTerritorios);

    // ataque
    while(1) {
        printf("\n--- Turno de Ataque ---\n");
        printf("Escolha o territorio atacante (1 a %d): ", numTerritorios);
        scanf("%d", &atacante_idx);

        printf("Escolha o territorio defensor (1 a %d): ", numTerritorios);
        scanf("%d", &defensor_idx);

        // Validação básica para evitar escolhas inválidas.
        if (atacante_idx < 1 || atacante_idx > numTerritorios ||
            defensor_idx < 1 || defensor_idx > numTerritorios) {
            printf("Escolha invalida. Tente novamente.\n");
            continue;
        }

        // obtem os ponteiros para os territórios para usar na função de ataque
        Territorio* atacante = &mapa[atacante_idx - 1];
        Territorio* defensor = &mapa[defensor_idx - 1];

        // Regras do jogo para evitar ataques inválidos.
        if (atacante == defensor) {
            printf("Um territorio nao pode atacar a si mesmo.\n");
            continue;
        }

        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Nao e possivel atacar um territorio da mesma cor.\n");
            continue;
        }
        
        if (atacante->tropas <= 1) {
            printf("O territorio atacante deve ter mais de 1 tropa.\n");
            continue;
        }

        // Chama a função de ataque, que vai definir a batalha
        atacar(atacante, defensor);

        printf("\n--- Mapa apos o ataque ---\n");
        exibirTerritorios(mapa, numTerritorios);
    }
    
    // libera a memória alocada dinamicamente.
    liberarMemoria(mapa);
    
    return 0;
}

//Implementação das Funções

// substitui o loop de cadastro do seu código anterior
void cadastrarTerritorios(Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

//exibe os territórios, agora usando um ponteiro.
void exibirTerritorios(Territorio* mapa, int numTerritorios) {
    for (int i = 0; i < numTerritorios; i++) {
        printf("Territorio %d: %s (%s) - %d tropas\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque que simula a batalha.
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) ataca %s (%s)!\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    
    // Rolagem de dados aleatórios para cada lado.
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
        atacante->tropas -= 1;
    }
}

// Função para liberar a memória alocada.
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada.\n");
}
