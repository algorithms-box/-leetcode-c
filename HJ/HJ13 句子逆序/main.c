#include <ctype.h>
#include <stdio.h>
#include <string.h>

void reverse_string(char* str, int start, int end);
void reverse_words(char* sentence);

int main() {
  char words[1000];

  fgets(words, 1000, stdin);

  int input_len = strlen(words);

  if (words[input_len - 1] == '\n') {
    words[input_len - 1] = '\0';
    input_len = input_len - 1;
  }

  reverse_words(words);

  printf("%s\n", words);
  return 0;
}

void reverse_string(char* str, int start, int end) {
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

void reverse_words(char* sentence) {
  int len = strlen(sentence);

  reverse_string(sentence, 0, len - 1);

  int start = 0;
  for (int i = 0; i <= len; i++) {
    if (isspace(sentence[i]) || i == len) {
      reverse_string(sentence, start, i - 1);
      start = i + 1;
    }
  }
}