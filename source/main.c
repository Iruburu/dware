#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Constantes de tamanho maximo
*/
#define MAX_WORD 64  // tamanho maximo de cada palavra
#define MAX_LINE 128 // tamanho maximo de cada linha do arquivo

/*
    Matriz que guarda 6 sequencias de 5 numeros aleatorios (1 a 6)
    Cada linha representa um "numero Diceware"
*/
int diceNumbers[6][5];

/*
    Vetor que guarda as 6 palavras finais escolhidas
*/
char selectedWords[6][MAX_WORD];

/*
    Ponteiro para o arquivo wordlist
*/
FILE *wordlist;

/*
    Converte uma linha da matriz diceNumbers em um inteiro
    Exemplo: [1][2][3][4][5] -> 12345
*/
int buildNumberFromRow(int row)
{
    int result = 0;

    // pesos para cada casa decimal
    int multipliers[] = {10000, 1000, 100, 10, 1};

    for (int i = 0; i < 5; i++)
    {
        result += diceNumbers[row][i] * multipliers[i];
    }

    return result;
}

/*
    Verifica se a linha do arquivo contem o numero desejado
    Se encontrar, copia a palavra para o buffer de saida

    Retorna:
    1 -> palavra encontrada
    0 -> nao encontrada ou linha invalida
*/
int extractWordFromLine(char *line, int targetNumber, char *output, size_t outputSize)
{
    char buffer[MAX_LINE];

    // copia a linha original para evitar modificar o buffer externo
    strcpy(buffer, line);

    // separa o numero e a palavra
    char *numberStr = strtok(buffer, " ");
    char *wordStr = strtok(NULL, " \n");

    // valida a linha
    if (!numberStr || !wordStr)
        return 0;

    // converte o numero alvo para string
    char targetStr[6];
    snprintf(targetStr, sizeof(targetStr), "%d", targetNumber);

    // compara os numeros
    if (strcmp(targetStr, numberStr) == 0)
    {
        strncpy(output, wordStr, outputSize - 1);
        output[outputSize - 1] = '\0';
        return 1;
    }

    return 0;
}

int main(void)
{
    // inicializa o gerador de numeros aleatorios
    srand(time(NULL));

    /*
        Gera os numeros aleatorios (1 a 6)
        6 linhas, cada uma com 5 numeros
    */
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            diceNumbers[row][col] = (rand() % 6) + 1;
        }
    }

    /*
    Tenta obter o caminho da wordlist a partir da variavel de ambiente
    DICEWARE_WORDLIST.
    */
    const char *wordlistPath = getenv("DICEWARE_WORDLIST");

    if (!wordlistPath)
        wordlistPath = "/usr/share/diceware/wordlist.txt";

    // abre o arquivo de palavras
    wordlist = fopen(wordlistPath, "r");
    if (!wordlist)
    {
        perror("Erro ao abrir wordlist");
        return 1;
    }

    char line[MAX_LINE];

    /*
        Para cada uma das 6 palavras:
        - percorre o arquivo inteiro
        - procura o numero correspondente
        - volta o ponteiro do arquivo ao inicio
    */
    for (int i = 0; i < 6; i++)
    {
        int targetNumber = buildNumberFromRow(i);

        while (fgets(line, MAX_LINE, wordlist))
        {
            extractWordFromLine(
                line,
                targetNumber,
                selectedWords[i],
                sizeof(selectedWords[i]));
        }

        // volta ao inicio do arquivo para a proxima palavra
        rewind(wordlist);
    }

    /*
        Exibe as 6 palavras separadas por espaco
    */
    for (int i = 0; i < 6; i++)
    {
        printf("%s", selectedWords[i]);

        if (i < 5)
            printf(" ");
    }

    printf("\n");

    fclose(wordlist);
    return 0;
}