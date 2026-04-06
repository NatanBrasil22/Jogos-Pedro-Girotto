#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* ============================================================ */
/*                        UTILIDADES                              */
/* ============================================================ */

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_inteiro(int min, int max) {
    char buffer[64];
    int valor;
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            limpar_buffer();
            printf("Entrada invalida. Digite um numero entre %d e %d: ", min, max);
            continue;
        }
        if (sscanf(buffer, "%d", &valor) != 1) {
            printf("Entrada invalida. Digite um numero entre %d e %d: ", min, max);
            continue;
        }
        if (valor < min || valor > max) {
            printf("Valor fora do intervalo. Digite entre %d e %d: ", min, max);
            continue;
        }
        return valor;
    }
}

int jogar_novamente(void) {
    char op;
    printf("\nDeseja jogar novamente? (S/N): ");
    op = tolower(getchar());
    limpar_buffer();
    return (op == 's');
}

void voltar_ao_menu(void) {
    char op;
    printf("\nDeseja jogar novamente? (S/N) ou digite 'M' para voltar ao menu: ");
    op = tolower(getchar());
    limpar_buffer();
    while (op != 's' && op != 'n' && op != 'm') {
        printf("Opcao invalida. Digite S (jogar), N (sair) ou M (menu): ");
        op = tolower(getchar());
        limpar_buffer();
    }
    /* retorna 0=sair para main, 1=jogar de novo, 2=voltar menu */
    if (op == 'n') exit(0);
    if (op == 'm') return;
}

/* retorna: 0=menu, 1=jog denovo */
int opcao_posparto(void) {
    char op;
    while (1) {
        printf("\n--- Jogo finalizado ---\n");
        printf("[S] Jogar novamente  |  [M] Voltar ao menu  |  [N] Sair\n");
        printf("Escolha: ");
        op = tolower(getchar());
        limpar_buffer();
        if (op == 's') return 1;
        if (op == 'n') { printf("Ate logo!\n"); exit(0); }
        if (op == 'm') return 0;
        printf("Opcao invalida.\n");
    }
}

/* ============================================================ */
/*                     JOGO 1: PERGUNTA E RESPOSTA                */
/* ============================================================ */

typedef struct {
    char pergunta[256];
    char alternativas[4][80];
    int correta; /* 0-3 */
} Pergunta;

Pergunta banco_perguntas[] = {
    {
        "Qual e a capital do Brasil?",
        {"Sao Paulo", "Brasilia", "Rio de Janeiro", "Salvador"},
        1
    },
    {
        "Qual e o maior planeta do Sistema Solar?",
        {"Terra", "Marte", "Jupiter", "Saturno"},
        2
    },
    {
        "Quem pintou a Mona Lisa?",
        {"Michelangelo", "Da Vinci", "Rafael", "Donatello"},
        1
    },
    {
        "Qual e o elemento quimico representado pelo simbolo 'O'?",
        {"Osmio", "Ouro", "Oxigenio", "Oganesson"},
        2
    },
    {
        "Em que ano o homem pisou na Lua pela primeira vez?",
        {"1959", "1965", "1969", "1972"},
        2
    }
};

void jogo_pergunta_resposta(void) {
    int pontuacao = 0;
    int resposta;
    int i;

    printf("\n=== PERGUNTA E RESPOSTA ===\n");
    printf("Responda 5 perguntas de multipla escolha.\n");
    printf("Cada pergunta tem 4 alternativas, apenas uma correta.\n\n");

    for (i = 0; i < 5; i++) {
        Pergunta *p = &banco_perguntas[i];
        printf("Pergunta %d: %s\n", i + 1, p->pergunta);
        for (int j = 0; j < 4; j++) {
            printf("  [%d] %s\n", j + 1, p->alternativas[j]);
        }
        printf("Sua resposta (1-4): ");
        resposta = ler_inteiro(1, 4) - 1;

        if (resposta == p->correta) {
            printf(">> Acertou!\n");
            pontuacao++;
        } else {
            printf(">> Errou! A correta era: [%d] %s\n",
                   p->correta + 1, p->alternativas[p->correta]);
        }
        printf("\n");
    }

    printf("Pontuacao final: %d de 5\n", pontuacao);
}

/* ============================================================ */
/*                   JOGO 2: COBRA NA CAIXA!                      */
/* ============================================================ */

#define NUM_CAIXAS 5
typedef enum { VAZIA, BOTAO, COBRA } Conteudo;

#define NUM_NOMES 7
const char *nomes_disponiveis[NUM_NOMES] = {
    "Carlos", "Ana", "Pedro", "Maria", "Joao", "Lucas", "Sofia"
};

void jogo_cobra_caixa(void) {
    char *nomes[2];
    int caixas_abertas[NUM_CAIXAS];
    Conteudo conteudo[NUM_CAIXAS];
    int turno;
    int escolha1, escolha2;
    int escolha, i, achou;

    printf("\n=== COBRA NA CAIXA! ===\n");
    printf("Ha 5 caixas fechadas. Entre elas:\n");
    printf("  1 BOTAO (vitoria instantanea)\n");
    printf("  1 COBRA (derrota instantanea)\n");
    printf("  3 CAIXAS VAZIAS\n\n");

    printf("Lista de nomes disponiveis:\n");
    for (i = 0; i < NUM_NOMES; i++)
        printf("  [%d] %s\n", i + 1, nomes_disponiveis[i]);

    printf("\nJogador 1, escolha seu nome (1-7): ");
    escolha1 = ler_inteiro(1, NUM_NOMES);
    nomes[0] = (char *)nomes_disponiveis[escolha1 - 1];

    printf("Jogador 2, escolha seu nome (1-7): ");
    escolha2 = ler_inteiro(1, NUM_NOMES);
    while (escolha2 == escolha1) {
        printf("Esse nome ja foi escolhido! Escolha outro (1-7): ");
        escolha2 = ler_inteiro(1, NUM_NOMES);
    }
    nomes[1] = (char *)nomes_disponiveis[escolha2 - 1];

    printf("\nJogadores: %s vs %s\n", nomes[0], nomes[1]);

    /* Sorteio de quem comeca */
    turno = rand() % 2;
    printf("\nSorteio: %s comeca!\n", nomes[turno]);

    /* Inicializar caixas */
    for (i = 0; i < NUM_CAIXAS; i++) caixas_abertas[i] = 0;

    /* Distribuir conteudo: sortear posicoes */
    for (i = 0; i < NUM_CAIXAS; i++) conteudo[i] = VAZIA;
    int pos_botao = rand() % NUM_CAIXAS;
    int pos_cobra;
    do { pos_cobra = rand() % NUM_CAIXAS; } while (pos_cobra == pos_botao);
    conteudo[pos_botao] = BOTAO;
    conteudo[pos_cobra] = COBRA;

    int caixas_restantes = NUM_CAIXAS;

    while (caixas_restantes > 0) {
        printf("\n--- Vez de %s ---\n", nomes[turno]);
        printf("Caixas fechadas:");
        achou = 0;
        for (i = 0; i < NUM_CAIXAS; i++) {
            if (!caixas_abertas[i]) {
                printf(" [%d]", i + 1);
                achou = 1;
            }
        }
        if (!achou) break;
        printf("\nEscolha uma caixa (1-5): ");
        escolha = ler_inteiro(1, 5) - 1;

        while (caixas_abertas[escolha]) {
            printf("Caixa %d ja esta aberta! Escolha outra (1-5): ", escolha + 1);
            escolha = ler_inteiro(1, 5) - 1;
        }

        caixas_abertas[escolha] = 1;
        caixas_restantes--;

        if (conteudo[escolha] == BOTAO) {
            printf(">> %s abriu a caixa %d e encontrou o BOTAO! %s VENCEU!\n",
                   nomes[turno], escolha + 1, nomes[turno]);
            return;
        } else if (conteudo[escolha] == COBRA) {
            printf(">> %s abriu a caixa %d e encontrou a COBRA! %s PERDEU!\n",
                   nomes[turno], escolha + 1, nomes[turno]);
            int vencedor = 1 - turno;
            printf(">> %s VENCEU!\n", nomes[vencedor]);
            return;
        } else {
            printf(">> %s abriu a caixa %d... VAZIA!\n", nomes[turno], escolha + 1);
        }

        turno = 1 - turno; /* troca turno */
    }

    printf("\nTodas as caixas abertas sem botao nem cobra! Empate!\n");
}

/* ============================================================ */
/*                     JOGO 3: GOUSMAS WAR                        */
/* ============================================================ */

void jogo_gousmas_war(void) {
    char nome1[50], nome2[50];
    JogadorG jog[2];
    int turno = 0;
    int acao, alvo, origem, destino;
    int k, furia_transferida;

    printf("\n=== GOUSMAS WAR ===\n");
    printf("Cada jogador possui 2 Gousmas com furia inicial 1.\n");
    printf("ACOES:\n");
    printf("  [1] ATACAR - Soma furia da sua Gousma ativa ao alvo inimigo.\n");
    printf("               Se furia do alvo > %d, ele e destruido.\n", FURIA_MORTAL);
    printf("  [2] DIVIDIR - Transfere furia entre suas Gousmas.\n");
    printf("               Se uma Gousma foi destruida, pode revive-la.\n");
    printf("PERDE quem ficar sem Gousmas ativas!\n\n");

    printf("Nome do Jogador 1: ");
    fgets(nome1, sizeof(nome1), stdin);
    nome1[strcspn(nome1, "\n")] = 0;

    printf("Nome do Jogador 2: ");
    fgets(nome2, sizeof(nome2), stdin);
    nome2[strcspn(nome2, "\n")] = 0;

    iniciar_jogador(&jog[0], nome1);
    iniciar_jogador(&jog[1], nome2);

    srand((unsigned int)time(NULL));
    turno = rand() % 2;
    printf("\nSorteio: %s comeca!\n", jog[turno].nome);

    while (1) {
        int ativo = turno;
        int inimigo = 1 - turno;

        if (contar_ativas(&jog[ativo]) == 0) {
            printf("\n%s ficou sem Gousmas ativas!\n", jog[ativo].nome);
            printf(">> %s VENCEU!\n", jog[inimigo].nome);
            return;
        }
        if (contar_ativas(&jog[inimigo]) == 0) {
            printf("\n%s ficou sem Gousmas ativas!\n", jog[inimigo].nome);
            printf(">> %s VENCEU!\n", jog[ativo].nome);
            return;
        }

        imprimir_status(&jog[0], &jog[1], ativo);
        printf("\n%s, escolha a acao:\n", jog[ativo].nome);
        printf("  [1] Atacar\n");
        printf("  [2] Dividir\n");
        printf("Acao: ");
        acao = ler_inteiro(1, 2);

        if (acao == 1) {
            printf("Escolha sua Gousma atacante:\n");
            for (k = 0; k < MAX_GOUSMAS; k++) {
                if (jog[ativo].gousmas[k].ativa)
                    printf("  [%d] %s (furia: %d)\n", k + 1, jog[ativo].gousmas[k].nome, jog[ativo].gousmas[k].furia);
            }
            origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
            while (!jog[ativo].gousmas[origem].ativa) {
                printf("Invalida! Escolha uma ativa: ");
                origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
            }

            printf("Escolha o alvo inimigo:\n");
            for (k = 0; k < MAX_GOUSMAS; k++) {
                if (jog[inimigo].gousmas[k].ativa)
                    printf("  [%d] %s (furia: %d)\n", k + 1, jog[inimigo].gousmas[k].nome, jog[inimigo].gousmas[k].furia);
            }
            alvo = ler_inteiro(1, MAX_GOUSMAS) - 1;
            while (!jog[inimigo].gousmas[alvo].ativa) {
                printf("Invalido! Escolha um inimigo ativo: ");
                alvo = ler_inteiro(1, MAX_GOUSMAS) - 1;
            }

            jog[inimigo].gousmas[alvo].furia += jog[ativo].gousmas[origem].furia;
            printf(">> Atacou! %s do inimigo agora tem %d de furia.\n", jog[inimigo].gousmas[alvo].nome, jog[inimigo].gousmas[alvo].furia);

            if (jog[inimigo].gousmas[alvo].furia > FURIA_MORTAL) {
                jog[inimigo].gousmas[alvo].ativa = 0;
                printf(">> %s foi DESTROIDA!\n", jog[inimigo].gousmas[alvo].nome);
            }
            if (jog[ativo].gousmas[origem].furia > 1) jog[ativo].gousmas[origem].furia--;

        } else {
            /* DIVIDIR / REVIVER */
            int g1_ativa = jog[ativo].gousmas[0].ativa;
            int g2_ativa = jog[ativo].gousmas[1].ativa;

            if (g1_ativa && g2_ativa) {
                /* Se as duas estao vivas, verifica se alguma tem mais de 1 para dividir */
                if (jog[ativo].gousmas[0].furia == 1 && jog[ativo].gousmas[1].furia == 1) {
                    printf("\nERRO: Ambas as Gousmas tem furia 1. Nao ha o que dividir!\n");
                    continue; 
                }

                printf("Escolha a Gousma fonte (furia > 1):\n");
                origem = ler_inteiro(1, 2) - 1;
                while (jog[ativo].gousmas[origem].furia <= 1) {
                    printf("Essa Gousma nao tem furia para dividir! Escolha outra: ");
                    origem = ler_inteiro(1, 2) - 1;
                }

                destino = 1 - origem;
                printf("Transferindo de %s para %s.\n", jog[ativo].gousmas[origem].nome, jog[ativo].gousmas[destino].nome);
                printf("Quanta furia transferir (1-%d): ", jog[ativo].gousmas[origem].furia - 1);
                
                furia_transferida = ler_inteiro(1, jog[ativo].gousmas[origem].furia - 1);
                jog[ativo].gousmas[origem].furia -= furia_transferida;
                jog[ativo].gousmas[destino].furia += furia_transferida;

            } else {
                /* Uma esta morta: Reviver */
                int idx_viva = g1_ativa ? 0 : 1;
                int idx_morta = 1 - idx_viva;

                if (jog[ativo].gousmas[idx_viva].furia <= 1) {
                    printf("\nERRO: Sua unica Gousma viva tem furia 1. Nao pode reviver a outra!\n");
                    continue;
                }

                printf("Revivendo %s usando furia de %s.\n", jog[ativo].gousmas[idx_morta].nome, jog[ativo].gousmas[idx_viva].nome);
                printf("Quanta furia passar para a nova (1-%d): ", jog[ativo].gousmas[idx_viva].furia - 1);
                
                furia_transferida = ler_inteiro(1, jog[ativo].gousmas[idx_viva].furia - 1);
                jog[ativo].gousmas[idx_viva].furia -= furia_transferida;
                jog[ativo].gousmas[idx_morta].furia = furia_transferida;
                jog[ativo].gousmas[idx_morta].ativa = 1;
                printf(">> %s voltou a vida!\n", jog[ativo].gousmas[idx_morta].nome);
            }
        }
        turno = 1 - turno;
    }
}
/* ============================================================ */
/*                        MENU PRINCIPAL                          */
/* ============================================================ */

int main(void) {
    int opcao;

    srand((unsigned int)time(NULL));

    printf("==========================================\n");
    printf("         MINIJOgos - Trabalho Final       \n");
    printf("==========================================\n");

    while (1) {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("[1] Pergunta e Resposta\n");
        printf("[2] Cobra na Caixa!\n");
        printf("[3] Gousmas War\n");
        printf("[4] Sair\n");
        printf("Escolha: ");
        opcao = ler_inteiro(1, 4);

        switch (opcao) {
            case 1:
                jogo_pergunta_resposta();
                if (!opcao_posparto()) continue;
                break;
            case 2:
                jogo_cobra_caixa();
                if (!opcao_posparto()) continue;
                break;
            case 3:
                jogo_gousmas_war();
                if (!opcao_posparto()) continue;
                break;
            case 4:
                printf("Ate logo!\n");
                return 0;
        }
    }
}
