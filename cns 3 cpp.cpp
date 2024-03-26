#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

// Function to encrypt the message using Hill Cipher
void hill_encrypt(char *message, int keyMatrix[][3], int len) {
    int cipher[len];
    int i, j, k;

    for (i = 0; i < len; i += 3) {
        for (j = 0; j < 3; j++) {
            cipher[i + j] = 0;
            for (k = 0; k < 3; k++) {
                cipher[i + j] += (keyMatrix[j][k] * (message[i + k] - 'A'));
            }
            cipher[i + j] %= 26;
        }
    }

    printf("Encrypted Message: ");
    for (i = 0; i < len; i++) {
        printf("%c", cipher[i] + 'A');
    }
    printf("\n");
}

// Function to calculate the modular inverse
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;

        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to decrypt the message using Hill Cipher
void hill_decrypt(int cipher[], int keyMatrix[][3], int len) {
    int plain[len];
    int i, j, k;
    int adj[3][3], det;

    // Calculate determinant
    det = keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) -
          keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]) +
          keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]);

    // Calculate adjoint matrix
    adj[0][0] = keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1];
    adj[0][1] = keyMatrix[0][2] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][2];
    adj[0][2] = keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1];
    adj[1][0] = keyMatrix[1][2] * keyMatrix[2][0] - keyMatrix[1][0] * keyMatrix[2][2];
    adj[1][1] = keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0];
    adj[1][2] = keyMatrix[0][2] * keyMatrix[1][0] - keyMatrix[0][0] * keyMatrix[1][2];
    adj[2][0] = keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0];
    adj[2][1] = keyMatrix[0][1] * keyMatrix[2][0] - keyMatrix[0][0] * keyMatrix[2][1];
    adj[2][2] = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];

    // Apply modulo inverse
    int inv_det = mod_inverse(det, 26);

    // Multiply inverse(det) with adjoint matrix
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            adj[i][j] = (adj[i][j] * inv_det) % 26;
            if (adj[i][j] < 0)
                adj[i][j] += 26;
        }
    }

    // Multiply adjoint matrix with the cipher to get the plain text
    for (i = 0; i < len; i += 3) {
        for (j = 0; j < 3; j++) {
            plain[i + j] = 0;
            for (k = 0; k < 3; k++) {
                plain[i + j] += (adj[j][k] * cipher[i + k]);
            }
            plain[i + j] %= 26;
        }
    }

    printf("Decrypted Message: ");
    for (i = 0; i < len; i++) {
        printf("%c", plain[i] + 'A');
    }
    printf("\n");
}

int main() {
    char message[MAX_SIZE];
    int keyMatrix[3][3] = {{6, 24, 1},
                           {13, 16, 10},
                           {20, 17, 15}};
    int len, choice;

    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    len = strlen(message);
    if (message[len - 1] == '\n')
        message[len - 1] = '\0'; // Remove newline character

    printf("Choose operation:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            hill_encrypt(message, keyMatrix, len);
            break;
        case 2: {
            int cipher[len];
            int i;
            printf("Enter the cipher text (in uppercase letters): ");
            for (i = 0; i < len; i++) {
                scanf("%d", &cipher[i]);
            }
            hill_decrypt(cipher, keyMatrix, len);
            break;
        }
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

