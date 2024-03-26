#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char playfairMatrix[SIZE][SIZE];

// Function to prepare the Playfair matrix
void preparePlayfairMatrix(char key[]) {
    int i, j, k, flag = 0, *visited = (int *)calloc(26, sizeof(int));

    // Initialize matrix with zeros
    memset(playfairMatrix, 0, sizeof(playfairMatrix));

    // Fill in the key
    for (i = 0; i < strlen(key); i++) {
        if (!visited[key[i] - 'A']) {
            visited[key[i] - 'A'] = 1;
            playfairMatrix[flag / SIZE][flag % SIZE] = key[i];
            flag++;
        }
    }

    // Fill in the rest of the alphabet
    for (k = 0; k < 26; k++) {
        if (visited[k] == 0 && k != ('Q' - 'A')) {
            playfairMatrix[flag / SIZE][flag % SIZE] = 'A' + k;
            flag++;
        }
    }
    free(visited);
}

// Function to find the positions of characters in the Playfair matrix
void findPosition(char ch, int *row, int *col) {
    int i, j;
    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of characters using the Playfair technique
void encryptPair(char a, char b) {
    int row1, col1, row2, col2;

    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);

    if (row1 == row2) {
        printf("%c%c", playfairMatrix[row1][(col1 + 1) % SIZE], playfairMatrix[row2][(col2 + 1) % SIZE]);
    } else if (col1 == col2) {
        printf("%c%c", playfairMatrix[(row1 + 1) % SIZE][col1], playfairMatrix[(row2 + 1) % SIZE][col2]);
    } else {
        printf("%c%c", playfairMatrix[row1][col2], playfairMatrix[row2][col1]);
    }
}

// Function to encrypt a message using the Playfair technique
void encrypt(char message[]) {
    int i;
    for (i = 0; i < strlen(message); i += 2) {
        if (message[i] == message[i + 1]) {
            printf("%c%c", message[i], 'X');
            i--;
        } else {
            encryptPair(message[i], message[i + 1]);
        }
    }
}

// Function to decrypt a message using the Playfair technique
void decrypt(char message[]) {
    int i;
    for (i = 0; i < strlen(message); i += 2) {
        encryptPair(message[i], message[i + 1]);
    }
}

int main() {
    char key[100], message[1000];

    // Input key
    printf("Enter key: ");
    scanf("%s", key);

    // Prepare Playfair matrix
    preparePlayfairMatrix(key);

    // Input message
    printf("Enter message: ");
    scanf("%s", message);

    // Encrypt message
    printf("Encrypted message: ");
    encrypt(message);
    printf("\n");

    // Decrypt message
    printf("Decrypted message: ");
    decrypt(message);
    printf("\n");

    return 0;
}

