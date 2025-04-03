#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PALAVRAS 1000   //número máximo de palavras permitidas do arquivo
#define MAX_TAMANHO 20      //tamanho máximo de cada palavra
#define NUM_ALEATORIAS 5    //número de palavras aleatórias
#define ALFABETO 26         //tamanho do alfabeto

int carregarPalavras(char *pal[], int *totPalavras, int minTam, int maxTam);
int exibirPalavrasAleatorias(char *pal[], int totPalavras);
void arrayPalavra(char *palavra, char letras[]);
void limparTela();
void erroForca(int err);
void underline(int T, int ok, char palavra[], int acertos[]);

int main() {
    char *palavras[MAX_PALAVRAS]; 
    int totalPalavras = 0;
    int palavraGerada;
    char letras_usadas[ALFABETO] = {0}; //inicializa o array de letras usadas
    int erro = 0;
    int acertos[MAX_TAMANHO] = {0};
    char letraUser;

    //carrega palavras do arquivo com tamanhos definidos 
    if (carregarPalavras(palavras, &totalPalavras, 4, 10) != 0) {
        return 1;
    }    

    //seleciona palavra aleatoria
    palavraGerada = exibirPalavrasAleatorias(palavras, totalPalavras);
    if (palavraGerada == -1) {
        return 1;
    }

    //transforma a palavra em um array de letras
    char letras[MAX_TAMANHO];
    arrayPalavra(palavras[palavraGerada], letras);
    int tamanhoPalavra = strlen(letras);

    //o jogo!
    while (erro < 6) {
        limparTela();
        erroForca(erro);    //exibe a forca
        printf("letras usadas: %s\n", letras_usadas);
        
        //exibe os espaços das letras
        underline(tamanhoPalavra, erro, letras, acertos);

        printf("\ndigite uma letra: ");
        scanf(" %c", &letraUser);

        //verifica se a letra já foi usada
        if (strchr(letras_usadas, letraUser) != NULL) {
            printf("você já usou essa letra!\n");
            continue;
        }

        // adiciona a letra ao array de usadas
        strncat(letras_usadas, &letraUser, 1);

        int acertou = 0;
        for (int j = 0; j < tamanhoPalavra; j++) {
            if (letraUser == letras[j]) {
                acertos[j] = 1; //pontua acerto
                acertou = 1;
            }
        }

        if (!acertou) {
            erro++; //
        }

        //verifica se o jogador venceu
        int venceu = 1;
        for (int j = 0; j < tamanhoPalavra; j++) {
            if (!acertos[j]) {
                venceu = 0;
                break;
            }
        }
        if (venceu) {
            printf("\nParabéns! você acertou a palavra: %s\n", letras);
            break;
        }
    }

    if (erro >= 6) {
        printf("\nGame over! a palavra era: %s\n", letras);
    }

    //libera memória
    for (int i = 0; i < totalPalavras; i++) {
        free(palavras[i]);
    }

    return 0;
}

//limpa a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// exibe a forca de acordo com o número de erros
void erroForca(int err){
    const char *forca[] = {
        "\n##################### jogo da forca! #####################\n"
        "  ______\n"
        " |      |\n"
        " |      \n"
        " |      \n"
        " |      \n"
        "_|_\n",
        
        "\n##################### jogo da forca! #####################\n"
        "  ______\n"
        " |      |\n"
        " |      O\n"
        " |      \n"
        " |      \n"
        "_|_\n",
        
        "\n##################### jogo da forca! #####################\n"
        "  ______\n"
        " |      |\n"
        " |      O\n"
        " |      |\n"
        " |      \n"
        "_|_\n",

        "\n##################### jogo da forca! #####################\n"
        "  ______\n"
        " |      |\n"
        " |      O\n"
        " |     /|\n"
        " |      \n"
        "_|_\n",

        "\n##################### jogo da forca! #####################\n"
        "  ______\n"
        " |      |\n"
        " |      O\n"
        " |     /|\\ \n"
        " |      \n"
        "_|_\n",

        "\n##################### jogo da forca! #####################\n"
        "  ______\n"
        " |      |\n"
        " |      O\n"
        " |     /|\\ \n"
        " |     / \n"
        "_|_\n",

        "\n##################### jogo da forca! #####################\n"
        "  ______\n"
        " |      |\n"
        " |      O\n"
        " |     /|\\ \n"
        " |     / \\ \n"
        "_|_\n"
    };
    printf("%s", forca[err]);
}

//transforma a palavra em um array de letras
void arrayPalavra(char *palavra, char letras[]) {
    strcpy(letras, palavra);
}

//carrega palavras do arquivo "palavras.txt"
int carregarPalavras(char *pal[], int *totPalavras, int minTam, int maxTam) {
    char buffer[MAX_TAMANHO];
    FILE *arquivo = fopen("palavras.txt", "r");

    if (arquivo == NULL) {
        printf("erro ao abrir o arquivo!\n");
        return 1;
    }

    while (fgets(buffer, MAX_TAMANHO, arquivo) != NULL && *totPalavras < MAX_PALAVRAS) {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        int tamanho = strlen(buffer);
        if (tamanho >= minTam && tamanho <= maxTam) { //filtra pelo tamanho
            pal[*totPalavras] = strdup(buffer);
            (*totPalavras)++;
        }
    }
    fclose(arquivo);
    return 0;
}

//seleciona uma palavra aleatória
int exibirPalavrasAleatorias(char *pal[], int totPalavras) {
    if (totPalavras == 0) {
        printf("nenhuma palavra carregada!\n");
        return -1;
    }
    srand(time(NULL));
    return rand() % totPalavras;
}

//exibe os espaços para as letras acertadas
void underline(int T, int ok, char palavra[], int acertos[]) {
    printf("palavra: ");
    for (int i = 0; i < T; i++) {
        if (acertos[i]) {
            printf("%c ", palavra[i]);
        } else {
            printf("_ ");
        }        
    }
    printf("\n");
}