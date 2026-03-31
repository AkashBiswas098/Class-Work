#include <ctype.h>
#include <stdio.h>
#include <string.h>

char m[5][5];

void genMatrix(char key[]) {
  int k = 0, used[26] = {0};
  for (int i = 0; key[i]; i++) {
    char c = toupper(key[i]);
    if (c == 'J')
      c = 'I';
    if (c < 'A' || c > 'Z' || used[c - 'A'])
      continue;
    m[k / 5][k % 5] = c;
    used[c - 'A'] = 1;
    k++;
  }
  for (int i = 0; i < 26; i++)
    if (i + 'A' != 'J' && !used[i])
      m[k / 5][k % 5] = i + 'A', k++;
}

void findPos(char c, int *r, int *col) {
  if (c == 'J')
    c = 'I';
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (m[i][j] == c) {
        *r = i;
        *col = j;
        return;
      }
}

void prepareText(char in[], char out[]) {
  int j = 0;
  for (int i = 0; in[i]; i++) {
    if (!isalpha(in[i]))
      continue;
    char c = toupper(in[i]);
    if (c == 'J')
      c = 'I';
    if (j % 2 == 1 && out[j - 1] == c)
      out[j++] = 'X';
    out[j++] = c;
  }
  if (j % 2)
    out[j++] = 'X';
  out[j] = '\0';
}

// dir=1 for encrypt, dir=4 for decrypt
void process(char text[], char res[], int dir) {
  int k = 0;
  for (int i = 0; text[i]; i += 2) {
    int r1, c1, r2, c2;
    findPos(text[i], &r1, &c1);
    findPos(text[i + 1], &r2, &c2);
    if (r1 == r2) {
      res[k++] = m[r1][(c1 + dir) % 5];
      res[k++] = m[r2][(c2 + dir) % 5];
    } else if (c1 == c2) {
      res[k++] = m[(r1 + dir) % 5][c1];
      res[k++] = m[(r2 + dir) % 5][c2];
    } else {
      res[k++] = m[r1][c2];
      res[k++] = m[r2][c1];
    }
  }
  res[k] = '\0';
}

int main() {
  char key[100], text[100], prepared[200], enc[200], dec[200];

  printf("Enter key: ");
  fgets(key, sizeof(key), stdin);
  key[strcspn(key, "\n")] = '\0';

  printf("Enter plaintext: ");
  fgets(text, sizeof(text), stdin);
  text[strcspn(text, "\n")] = '\0';

  genMatrix(key);
  prepareText(text, prepared);

  process(prepared, enc, 1);
  printf("\nEncrypted: %s", enc);

  process(enc, dec, 4);
  printf("\nDecrypted: %s", dec);

  return 0;
}