#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

int main() {
  char str[MAX_LENGTH];
  fgets(str, MAX_LENGTH, stdin);

  // Remove the newline character at the end if present
  int endIndex = strlen(str);
  if (str[endIndex - 1] == '\n') {
    str[endIndex - 1] = '\0';
    endIndex--;
  }

  // Process each character in the string
  for (int i = 0; i < endIndex; i++) {
    if (isspace(str[i])) {
      continue;
    } else {
      if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' ||
          str[i] == 'u' || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' ||
          str[i] == 'O' || str[i] == 'U') {
        str[i] = toupper(str[i]);
      } else {
        str[i] = tolower(str[i]);
      }
    }
  }

  printf("%s\n", str);

  return 0;
}