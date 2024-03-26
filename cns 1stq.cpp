#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char message[], int key) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            if (islower(message[i])) {
                message[i] = 'a' + (message[i] - 'a' + key) % 26;
            } else if (isupper(message[i])) {
                message[i] = 'A' + (message[i] - 'A' + key) % 26;
            }
        }
    }
}

void decrypt(char message[], int key) {
    encrypt(message, 26 - key); 
}

int main() {
    char message[1000];
    int key;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
 
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0';
    }

    printf("Enter key: ");
    scanf("%d", &key);

    encrypt(message, key);
    printf("Encrypted message: %s\n", message);

    decrypt(message, key);
    printf("Decrypted message: %s\n", message);

    return 0;
}

