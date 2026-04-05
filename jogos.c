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

#define MAX_GOUSMAS 2
#define FURIA_MORTAL 5

typedef struct {
    char nome[3]; /* "G1", "G2" */
    int furia;
    int ativa;
} Gousma;

typedef struct {
    char nome[50];
    Gousma gousmas[MAX_GOUSMAS];
    int furia_global; /* furiabase que gera novas gousmas */
} JogadorG;

void iniciar_jogador(JogadorG *j, const char *nome) {
    int k;
    strncpy(j->nome, nome, sizeof(j->nome) - 1);
    j->nome[sizeof(j->nome) - 1] = 0;
    j->furia_global = 1;
    for (k = 0; k < MAX_GOUSMAS; k++) {
        j->gousmas[k].nome[0] = 'G';
        j->gousmas[k].nome[1] = (char)('1' + k);
        j->gousmas[k].nome[2] = 0;
        j->gousmas[k].furia = 1;
        j->gousmas[k].ativa = 1;
    }
}

int contar_ativas(JogadorG *j) {
    int c = 0, k;
    for (k = 0; k < MAX_GOUSMAS; k++) {
        if (j->gousmas[k].ativa) c++;
    }
    return c;
}

void imprimir_status(JogadorG *p1, JogadorG *p2, int turno) {
    int k;
    printf("\n========== GOUSMAS WAR ==========\n");
    printf("--- %s %s ---\n", p1->nome, turno == 0 ? "(SUA VEZ)" : "");
    for (k = 0; k < MAX_GOUSMAS; k++) {
        if (p1->gousmas[k].ativa)
            printf("  %s: Furia = %d\n", p1->gousmas[k].nome, p1->gousmas[k].furia);
        else
            printf("  %s: DESTROIDA\n", p1->gousmas[k].nome);
    }
    printf("--- %s %s ---\n", p2->nome, turno == 1 ? "(SUA VEZ)" : "");
    for (k = 0; k < MAX_GOUSMAS; k++) {
        if (p2->gousmas[k].ativa)
            printf("  %s: Furia = %d\n", p2->gousmas[k].nome, p2->gousmas[k].furia);
        else
            printf("  %s: DESTROIDA\n", p2->gousmas[k].nome);
    }
    printf("=================================\n");
}

void jogo_gousmas_war(void) {
    char nome1[50], nome2[50];
    JogadorG jog[2];
    int turno = 0;
    int acao, alvo, origem, destino;
    int k, idx_destino, furia_transferida;

    printf("\n=== GOUSMAS WAR ===\n");
    printf("Cada jogador possui 2 Gousmas com furia inicial 1.\n");
    printf("ACOES:\n");
    printf("  [1] ATACAR - Soma furia da sua Gousma ativa ao alvo inimigo.\n");
    printf("             Se furia do alvo > %d, ele e destruido.\n", FURIA_MORTAL);
    printf("  [2] DIVIDIR - Transfere furia entre suas Gousmas.\n");
    printf("             Se uma Gousma foi destruida, pode revive-la.\n");
    printf("PERDE quem ficar sem Gousmas ativas!\n\n");

    printf("Nome do Jogador 1: ");
    fgets(nome1, sizeof(nome1), stdin);
    nome1[strcspn(nome1, "\n")] = 0;

    printf("Nome do Jogador 2: ");
    fgets(nome2, sizeof(nome2), stdin);
    nome2[strcspn(nome2, "\n")] = 0;

    srand((unsigned int)time(NULL));
    turno = rand() % 2;
    printf("\nSorteio: %s comeca!\n", jog[turno].nome);

    iniciar_jogador(&jog[0], nome1);
    iniciar_jogador(&jog[1], nome2);

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
            /* ATACAR: escolher Gousma atacante (propria ativa) */
            printf("Escolha sua Gousma atacante:\n");
            for (k = 0; k < MAX_GOUSMAS; k++) {
                if (jog[ativo].gousmas[k].ativa)
                    printf("  [%d] %s (furia: %d)\n", k + 1,
                           jog[ativo].gousmas[k].nome, jog[ativo].gousmas[k].furia);
            }
            printf("Gousma: ");
            origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
            while (!jog[ativo].gousmas[origem].ativa) {
                printf("Essa Gousma esta destroida! Escolha outra: ");
                origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
            }

            /* escolher alvo inimigo (ativo) */
            printf("Escolha a Gousma inimiga alvo:\n");
            for (k = 0; k < MAX_GOUSMAS; k++) {
                if (jog[inimigo].gousmas[k].ativa)
                    printf("  [%d] %s (furia: %d)\n", k + 1,
                           jog[inimigo].gousmas[k].nome, jog[inimigo].gousmas[k].furia);
            }
            printf("Alvo: ");
            alvo = ler_inteiro(1, MAX_GOUSMAS) - 1;
            while (!jog[inimigo].gousmas[alvo].ativa) {
                printf("Essa Gousma esta destroida! Escolha outra: ");
                alvo = ler_inteiro(1, MAX_GOUSMAS) - 1;
            }

            jog[inimigo].gousmas[alvo].furia += jog[ativo].gousmas[origem].furia;
            printf("%s atacou a %s do inimigo com %s (furia %d)!\n",
                   jog[ativo].nome, jog[inimigo].gousmas[alvo].nome,
                   jog[ativo].gousmas[origem].nome, jog[ativo].gousmas[origem].furia);
            printf("%s agora tem furia %d.\n",
                   jog[inimigo].gousmas[alvo].nome, jog[inimigo].gousmas[alvo].furia);

            if (jog[inimigo].gousmas[alvo].furia > FURIA_MORTAL) {
                jog[inimigo].gousmas[alvo].ativa = 0;
                jog[inimigo].gousmas[alvo].furia = 0;
                printf(">> %s foi DESTROIDA!\n", jog[inimigo].gousmas[alvo].nome);
            }

            /* Gousma atacante perde 1 de furia no ataque (minimo 1) */
            if (jog[ativo].gousmas[origem].furia > 1)
                jog[ativo].gousmas[origem].furia--;
        } else {
            /* DIVIDIR: transferir furia entre Gousmas proprias */
            int tem_destuida = 0;
            for (k = 0; k < MAX_GOUSMAS; k++) {
                if (!jog[ativo].gousmas[k].ativa) { tem_destuida = 1; break; }
            }

            if (tem_destuida) {
                printf("Modo de reviver Gousma!\n");
                printf("Escolha a Gousma ativa como fonte (vai perder toda furia):\n");
                for (k = 0; k < MAX_GOUSMAS; k++) {
                    if (jog[ativo].gousmas[k].ativa)
                        printf("  [%d] %s (furia: %d)\n", k + 1,
                               jog[ativo].gousmas[k].nome, jog[ativo].gousmas[k].furia);
                }
                printf("Fonte: ");
                origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
                while (!jog[ativo].gousmas[origem].ativa) {
                    printf("Gousma destroida! Escolha uma ativa: ");
                    origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
                }

                printf("Escolha a Gousma destroida para reviver:\n");
                for (k = 0; k < MAX_GOUSMAS; k++) {
                    if (!jog[ativo].gousmas[k].ativa)
                        printf("  [%d] %s (DESTROIDA)\n", k + 1, jog[ativo].gousmas[k].nome);
                }
                printf("Destino: ");
                destino = ler_inteiro(1, MAX_GOUSMAS) - 1;
                while (jog[ativo].gousmas[destino].ativa) {
                    printf("Essa Gousma ja esta ativa! Escolha uma destroida: ");
                    destino = ler_inteiro(1, MAX_GOUSMAS) - 1;
                }

                int furia_transferida = jog[ativo].gousmas[origem].furia;
                jog[ativo].gousmas[origem].furia = 1;
                jog[ativo].gousmas[destino].ativa = 1;
                jog[ativo].gousmas[destino].furia = furia_transferida;
                printf(">> %s reviveu com furia %d!\n",
                       jog[ativo].gousmas[destino].nome, furia_transferida);
            } else {
                /* Ambas ativas: transferir furia */
                printf("Escolha a Gousma fonte:\n");
                for (k = 0; k < MAX_GOUSMAS; k++) {
                    if (jog[ativo].gousmas[k].ativa)
                        printf("  [%d] %s (furia: %d)\n", k + 1,
                               jog[ativo].gousmas[k].nome, jog[ativo].gousmas[k].furia);
                }
                printf("Fonte: ");
                origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
                while (!jog[ativo].gousmas[origem].ativa) {
                    printf("Gousma destroida! Escolha outra: ");
                    origem = ler_inteiro(1, MAX_GOUSMAS) - 1;
                }

                printf("Escolha a Gousma destino:\n");
                for (k = 0; k < MAX_GOUSMAS; k++) {
                    if (k != origem && jog[ativo].gousmas[k].ativa)
                        printf("  [%d] %s (furia: %d)\n", k + 1,
                               jog[ativo].gousmas[k].nome, jog[ativo].gousmas[k].furia);
                }
                printf("Destino: ");
                destino = ler_inteiro(1, MAX_GOUSMAS) - 1;
                while (destino == origem || !jog[ativo].gousmas[destino].ativa) {
                    printf("Invalido! Escolha outra Gousma ativa: ");
                    destino = ler_inteiro(1, MAX_GOUSMAS) - 1;
                }

                printf("Quanta furia transferir (1-%d): ",
                       jog[ativo].gousmas[origem].furia - 1);
                furia_transferida = ler_inteiro(1, jog[ativo].gousmas[origem].furia - 1);

                jog[ativo].gousmas[origem].furia -= furia_transferida;
                jog[ativo].gousmas[destino].furia += furia_transferida;

                printf("%s transferiu %d de furia de %s para %s.\n",
                       jog[ativo].nome, furia_transferida,
                       jog[ativo].gousmas[origem].nome,
                       jog[ativo].gousmas[destino].nome);
            }
        }

        turno = inimigo; /* troca turno */
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
