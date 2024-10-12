#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 10000

int main() {
  char str[MAX_LENGTH];
  fgets(str, MAX_LENGTH, stdin);

  double word_count = 0.0;
  double weight = 0.0;
  int in_word = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    if (!isspace(str[i])) {
      weight++;
      in_word = 1;
    } else {
      if (in_word) {
        word_count++;
        in_word = 0;
      }
    }
  }

  // last char
  if (in_word) {
    word_count++;
  }

  if (word_count > 0) {
    // printf("%f\n", weight);
    // printf("%f\n", word_count);
    double result = weight / word_count;
    printf("%.2f\n", result);
  } else {
    printf("0.00\n");
  }

  return 0;
}