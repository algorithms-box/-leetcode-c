#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
  return strcmp((const char *)a, (const char *)b);
}

int main() {
  int n = 0;
  char str[100][100];
  char new[100];

  while (scanf("%s", &new) != EOF) {
    char *t = strtok(new, ",");
    while (t != NULL) {
      strcpy(str[n++], t);
      t = strtok(NULL, ",");
    }

    if (getchar() == '\n') {
      qsort(str, n, sizeof(str[0]), cmp);
      for (int i = 0; i < n - 1; i++) {
        printf("%s,", str[i]);
      }
      printf("%s\n", str[n - 1]);
      n = 0;
    }
  }

  return 0;
}
