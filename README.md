# Jogo da Forca 🎯

Um simples jogo da forca feito em C! Adivinhe a palavra, você tem 6 tentativas.

## Como rodar 🚀

Compile o código: (MinGW)

```bash
gcc forca.c -o forca
```
Execute:
```bash
./forca ou .\forca (windows)
```

## Como funciona?

O jogo escolhe uma palavra aleatória de um arquivo palavras.txt.

Você digita uma letra por vez.

Se a letra estiver na palavra, ela aparece no lugar certo.

Se errar, a forca vai sendo desenhada.

Se errar 6 vezes… ☠️

Se acertar todas as letras, você vence! 🏆

## Personalização ✍️

Você pode adicionar palavras ao palavras.txt.

Quer mudar a quantidade de erros permitidos? Edite o número no código na **linha 44**.

Quer aumentar ou diminuir o número de letras? Edite o código na **linha 28**.
