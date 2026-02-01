# dware

Gerador simples de senhas Diceware feito em C, usando wordlist externa.

Este projeto foi criado **exclusivamente para estudo da linguagem C**, com foco em:
- manipulação de strings
- uso de arquivos
- variáveis de ambiente
- organização de código em estilo Unix

Não é um projeto voltado a produção, mas sim aprendizado e prática.

---

## Descrição

O `dware` gera uma senha composta por **6 palavras aleatórias**, seguindo o método Diceware.

Para cada palavra, o programa:
1. Gera 5 números aleatórios entre 1 e 6
2. Converte esses números em um valor Diceware (ex: 15423)
3. Procura esse valor em uma wordlist
4. Retorna a palavra correspondente

O resultado final é uma senha formada por 6 palavras separadas por espaço.

---

## Sistema suportado

- Desenvolvido e testado em **Linux**
- Pode funcionar em outros sistemas Unix-like, mas não foi testado

---

## Wordlist (variável de ambiente)

O caminho da wordlist **não fica fixo no código**.

O programa espera que o caminho seja informado pela variável de ambiente:

```bash
DICEWARE_WORDLIST
