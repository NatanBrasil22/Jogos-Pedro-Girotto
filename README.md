# MiniJogos - Trabalho Final

## Descrição

Projeto contendo 3 minijogos desenvolvidos em linguagem C como trabalho final da disciplina.

## Jogos Implementados

1. **Pergunta e Resposta** - Quiz com 5 perguntas de multipla escolha (4 alternativas cada, 1 correta).
2. **Cobra na Caixa!** - Jogo de sorte para 2 jogadores com 5 caixas sorteadas (1 botao, 1 cobra, 3 vazias).
3. **Gousmas War** - Jogo de estrategia por turnos entre 2 jogadores com Gousmas, sistema de furia e acoes de ataque e divisao.

## Como Compilar e Executar

```bash
gcc jogos.c -o jogos.exe
jogos.exe
```

Ou abrir `jogos.c` no Dev-C++ pressionar `F9`.

## Tecnologias

- Linguagem C padrao
- Bibliotecas: `stdio.h`, `stdlib.h`, `string.h`, `time.h`, `ctype.h`

## Ferramentas de IA Utilizadas

Este projeto foi desenvolvido com o auxilio do **Claude Code** da Anthropic (https://github.com/anthropics/claude-code), modelo Claude, plano gratuito.

## Divisao das Contribuicoes

### O que os alunos fizeram

- Definicao completa das regras, mecanicas e requisitos de cada um dos 3 jogos.
- Elaboracao do documento de especificacao (PDF) detalhando comportamento esperado de cada jogo.
- Elaboracao e revisao do codigo gerado, identificando pontos que precisavam de ajuste (ex: substituir entrada de nome livre por lista de 7 nomes pre-definidos).
- Solicitacao de iteracoes e correcoes ao longo do desenvolvimento.
- Compilacao, testes e validacao final do projeto no ambiente de execucao.
- Criacao do repositorio no GitHub e organizacao dos arquivos do projeto.

### O que a IA fez

- Geracao da estrutura base do codigo (menu principal, funcoes auxiliares, validacao de entrada).
- Implementacao da logica de cada jogo em C de acordo com as especificacoes fornecidas pelo aluno.
- Ajustes e correcoes solicitadas pelo aluno durante o processo iterativo.

## Registro da Conversa com a IA

Abaixo seguem capturas de tela que demonstram como o Claude Code foi utilizado durante o desenvolvimento do projeto:

### Tela 1 - Especificacao inicial dos jogos

<!-- INSIRA O PRINT AQUI: documento PDF ou mensagem inicial com as regras --><img width="1090" height="632" alt="image" src="https://github.com/user-attachments/assets/d6a9be8c-2900-4c03-bc15-53027e6974db" />



### Tela 2 - Geracao da primeira versao do codigo

<!-- INSIRA O PRINT AQUI: Claude gerando o codigo C --><img width="872" height="389" alt="image" src="https://github.com/user-attachments/assets/1d10530e-014c-44f2-8458-4f84a305795e" />



### Tela 3 - Solicitacao de ajustes (nomes pre-definidos)

<!-- INSIRA O PRINT AQUI: aluno pedindo alteracao e Claude ajustando --><img width="1113" height="338" alt="image" src="https://github.com/user-attachments/assets/6997a393-1d31-4fa4-af43-6eb3d785ad27" />



### Tela 4 - Compilacao e codigo final

<!-- INSIRA O PRINT AQUI: resultado final ou terminal compilando --><img width="680" height="537" alt="image" src="https://github.com/user-attachments/assets/b6591126-3572-4301-ac77-ffbc6a42c613" />



---

## Referencias de Codigo de Fontes Externas

Todo o codigo-fonte em `jogos.c` foi gerado com auxilio de IA (Claude Code, Anthropic). Nao foram utilizados trechos de codigo de fontes como Stack Overflow, GitHub ou similares.

- Anthropic, Claude Code. Disponivel em: https://github.com/anthropics/claude-code
