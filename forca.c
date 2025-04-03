#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PALAVRAS 1000   //número máximo de palavras permitidas do arquivo
#define MAX_TAMANHO 20      //tamanho máximo de cada palavra
#define ALFABETO 26         //tamanho do alfabeto

int carregarPalavras(char *pal[], int *totPalavras, int minTam, int maxTam);
int exibirPalavrasAleatorias(char *pal[], int totPalavras);
void arrayPalavra(char *palavra, char letras[]);
void limparTela();
void erroForca(int err);
void underline(int T, int ok, char palavra[], int acertos[]);
void mudarCor(const char *cor);
void desenvolvidor(char *palavra);

int main() {
    char *palavras[MAX_PALAVRAS]; 
    int totalPalavras = 0;
    int palavraGerada;
    char letras_usadas[ALFABETO] = {0}; //inicializa o array de letras usadas
    int erro = 0;
    int acertos[MAX_TAMANHO] = {0};
    char letraUser;
    int modoDev = 0;

    //carrega palavras do arquivo com tamanhos definidos 
    if (carregarPalavras(palavras, &totalPalavras, 4, 10) != 0) {   //pode editar aqui
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
    while (erro < 6) {  //pode editar aqui
        limparTela();
        mudarCor("vermelho");
        erroForca(erro);    //exibe a forca
        mudarCor("");
        printf("\nLetras usadas: %s\n", letras_usadas);
        
        //modo dev
        if (modoDev) {
            mudarCor("verde");
            printf("\n[DevMode] Palavra secreta: %s\n", letras);
            mudarCor("");
        }

        //exibe os espaços das letras
        underline(tamanhoPalavra, erro, letras, acertos);

        printf("\nDigite uma letra: ");
        scanf(" %c", &letraUser);

        //continuacao modo dev
        if (letraUser == '9') {
            modoDev = 1;
            continue; //nao deixa contar 9 como uma tentativa
        }

        //verifica se a letra já foi usada
        if (strchr(letras_usadas, letraUser) != NULL) {
            mudarCor("vermelho");
            printf("Você já usou essa letra!\n");
            mudarCor("");
        
            printf("\nPressione ENTER para continuar...");
            getchar();  //captura o ENTER
            getchar();
        
            continue;
        }

        //adiciona a letra ao array de letras usadas
        strncat(letras_usadas, &letraUser, 1);

        int acertou = 0;
        for (int j = 0; j < tamanhoPalavra; j++) {
            if (letraUser == letras[j]) {
                acertos[j] = 1; //pontua acerto
                acertou = 1;
            }
        }

        if (!acertou) {
            erro++;
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
            limparTela();
            erroForca(erro);
            underline(tamanhoPalavra, erro, letras, acertos); //mostra a palavra completa
        
            mudarCor("verde");
            printf("\nParabéns! Você acertou a palavra: %s\n", letras);
            mudarCor("");
        
            break;
        }
        
    }

    if (erro >= 6) {
        mudarCor("vermelho");
        printf("\nGame over! A palavra era: %s\n", letras);
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

//exibe a forca
void erroForca(int err) {
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
        printf("Erro ao abrir o arquivo!\n");
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

//exibe os espaços das letras acertadas
void underline(int T, int ok, char palavra[], int acertos[]) {
    printf("\nPalavra: ");
    for (int i = 0; i < T; i++) {
        if (acertos[i]) {
            mudarCor("verde");
            printf("%c ", palavra[i]);
            mudarCor("");
        } else {
            mudarCor("azul");
            printf("_ ");
            mudarCor("");
        }        
    }
    printf("\n");
}

//cor
void mudarCor(const char *cor) {
    if (strcmp(cor, "vermelho") == 0) {
        printf("\033[1;31m"); // Muda para vermelho
    } else if (strcmp(cor, "verde") == 0) {
        printf("\033[1;32m"); // Muda para verde
    } else if (strcmp(cor, "azul") == 0) {
        printf("\033[1;34m"); // Muda para azul
    } else {
        printf("\033[0m"); // Reseta cor
    }
}

//modo dev
void desenvolvidor(char *palavra) {
    printf("\n[DevMode] Palavra secreta: %s\n", palavra);
}
