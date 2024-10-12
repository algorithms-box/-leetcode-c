#include <stdio.h>
#include <stdlib.h>

int main() {
  long long int a, b;
  while (scanf("%ld %ld", &a, &b) != EOF) {
    printf("%ld\n", (long long)(a + b));
  }

  return 0;
}
