#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function to convert char to number (A=0, ..., Z=25)
int charToNum(char c) {
  c = toupper(c); // handle lowercase
  return c - 'A';
}

// Function to convert number to char
char numToChar(int n) { return n + 'A'; }

int main() {
  char plaintext[100], key[100];
  int i, len;

  printf("Enter Plaintext: ");
  fgets(plaintext, sizeof(plaintext), stdin);

  printf("Enter Key (same length): ");
  fgets(key, sizeof(key), stdin);

  // Remove newline characters added by fgets
  plaintext[strcspn(plaintext, "\n")] = '\0';
  key[strcspn(key, "\n")] = '\0';

  len = strlen(plaintext);

  printf("\nEncrypted (XOR):");

  int cipher[100];

  // Encryption
  for (i = 0; i < len; i++) {

    if (plaintext[i] == ' ') { // handle spaces
      cipher[i] = -1;
      printf("  ");
      continue;
    }

    int p = charToNum(plaintext[i]);
    int k = charToNum(key[i]);

    cipher[i] = p ^ k;
    printf("%d ", cipher[i]);
  }

  printf("\n");

  // Show alphabet form
  printf("Cipher (letters): ");
  for (i = 0; i < len; i++) {
    if (cipher[i] == -1) {
      printf(" ");
    } else {
      printf("%c", numToChar(cipher[i] % 26));
    }
  }

  printf("\n");

  // Decryption
  printf("\nDecrypted: ");

  for (i = 0; i < len; i++) {

    if (cipher[i] == -1) {
      printf(" ");
      continue;
    }

    int p = cipher[i] ^ charToNum(key[i]);
    printf("%c", numToChar(p));
  }

  printf("\n");

  return 0;
}