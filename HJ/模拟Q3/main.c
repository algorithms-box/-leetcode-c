#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *x, char *y) {
  char temp = *x;
  *x = *y;
  *y = temp;
}

void printPermutation(char *str) {
  for (int i = 0; str[i]; i++) printf("%c", str[i]);
  printf("\n");
}

int permute(char *str, int start, int end) {
  static int count = 0;
  if (start == end) {
    // printPermutation(str);
    count++;
  } else {
    for (int i = start; i <= end; i++) {
      int repeated = 0;
      for (int j = start; j < i; j++) {
        if (str[i] == str[j]) {
          repeated = 1;
          break;
        }
      }
      if (repeated) continue;

      swap((str + start), (str + i));
      permute(str, start + 1, end);
      swap((str + start), (str + i));
    }
  }

  return count;
}

int main() {
  char str[26];
  //   printf("Enter a string of uppercase letters: ");
  scanf("%25s", str);

  int len = strlen(str);
  int count = permute(str, 0, len - 1);
  printf("%d\n", count);

  return 0;
}