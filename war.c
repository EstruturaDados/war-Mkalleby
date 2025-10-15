// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// criando struct
typedef struct{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//definindo constante para o tamanho máximo de territórios
#define quantidade_territorios 5
void listar(Territorio *territorios, int quantidade) {
    printf("\n-----------Lista de Territórios-----------\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%d° Território:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("--------------------------------------\n");
    }
}
char cor_missao[10]; // variável global para armazenar a cor da missão

void criarMissao(Territorio *territorios, int quantidade) {
    srand(time(NULL));
    int indice = rand() % quantidade;
    strcpy(cor_missao, territorios[indice].cor);

    printf("\n🔴 Missão criada: Destruir todos os territórios da cor '%s'\n", cor_missao);

    // Verificação imediata da missão
    int existe = 0;
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(territorios[i].cor, cor_missao) == 0 && territorios[i].tropas > 0) {
            existe = 1;
            break;
        }
    }

    if (!existe) {
        printf("✅ Missão já está concluída! Nenhum território da cor '%s' possui tropas.\n", cor_missao);
    } else {
        printf("⏳ Missão em andamento. Ainda existem territórios da cor '%s' com tropas.\n", cor_missao);
    }
}
void atacar (Territorio *atacante, Territorio *defensor){
    srand(time(NULL));
    
    int dado_atacante = rand() % 20;
    int dado_defensor = rand() % 20;
    
    if(dado_atacante > dado_defensor){
        printf("O %s tirou %d no dado",atacante->nome, dado_atacante);
        printf("\n");
        printf("O %s tirou %d no dado", defensor->nome, dado_defensor);
        printf("\n");
        printf("O territorio atacante %s venceu e o territorio defensor %s perdeu 1 tropa\n", atacante->nome, defensor->nome);
        defensor->tropas -= 1;
        printf("\n");
        
        if(defensor->tropas < 1){
            printf("O território %s de cor %s, conquistou o território %s de cor %s", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
            strcpy(defensor->cor, atacante->cor);
            printf("\n");
            printf("Agora o território %s é %s", defensor->nome, defensor->cor);
        }
    }else{
        printf("O %s tirou %d no dado",atacante->nome, dado_atacante);
        printf("\n");
        printf("O %s tirou %d no dado", defensor->nome, dado_defensor);
        printf("\n");
        printf("O territorio atacante %s perdeu e o territorio %s venceu\n", atacante->nome, defensor->nome);
        printf("\n");
    }
}
int main() {
    //definindo vetor com base na struct e no tamaho máximo
    Territorio *territorio = (Territorio *)calloc(quantidade_territorios, sizeof(Territorio));
    int atacante;
    int defensor;
    printf("JOGO WAR\n");
    
    //percorrendo cada índice para cadastrar o territorio
    for (int i = 0; i < quantidade_territorios; i++){
        printf("\n");
        printf("-----------Cadastre o %d° territorio-----------\n", i + 1);
        printf("\n");
        
        //cadastrando com base no índice atual no laço
        printf("Digite o nome do %d° território: ", i + 1);
        fgets(territorio[i].nome, sizeof(territorio[i].nome), stdin);
        territorio[i].nome[strcspn(territorio[i].nome, "\n")] = '\0';
        printf("\n");
        
        printf("Digite a cor %d° do territorio: ", i + 1);
        fgets(territorio[i].cor, sizeof(territorio[i].cor), stdin);
        territorio[i].cor[strcspn(territorio[i].cor, "\n")] = '\0';
        printf("\n");
        
        printf("Digite a quantidade de tropas do %d° territorio: ", i + 1);
        scanf("%d", &territorio[i].tropas);
        getchar();
        
        printf("\n");
    }
    
    //percorrendo cada índice cadastrado e printando na tela as informações
    criarMissao(territorio, quantidade_territorios);
    do {
        printf("\n");
        printf("-----------Lista de Territorios-----------\n");
        printf("\n");
        
        for (int j = 0; j < quantidade_territorios; j++){
        
        printf("%d° Territorio: \n", j + 1);
        printf("\n");
        printf("Territorio: %s", territorio[j].nome);
        printf("\n");
        printf("Cor: %s", territorio[j].cor);
        printf("\n");
        printf("Quantidade de tropas: %d\n", territorio[j].tropas);
        printf("\n");
        printf("--------------------------------------");
        printf("\n");
        }
        
        printf("Escolha um territorio para atacar (de 1 a %d, ou 0 pra sair): ", quantidade_territorios);
        scanf("%d", &atacante);
        getchar();
        printf("\n");
        
        printf("Escolha um territorio para defender (de 1 a %d, ou 0 pra sair): ", quantidade_territorios);
        scanf("%d", &defensor);
        getchar();
        printf("\n");
          
        if (atacante < 1 || atacante > quantidade_territorios || defensor < 1 || defensor > quantidade_territorios ||
        atacante == defensor) {
        printf("Escolha inválida.\n");
        }else{  
             atacar(&territorio[atacante - 1], &territorio[defensor - 1]);
        }
    } while(1);
    printf("\n");
    printf("Saindo do sistema");
    return 0;
}