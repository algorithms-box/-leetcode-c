#include <stdio.h>
#include <string.h>

int expandAroundCenter(const char *str, int left, int right) {
  while (left >= 0 && right < strlen(str) && str[left] == str[right]) {
    left--;
    right++;
  }
  return right - left - 1;
}

int longestPalindrome(const char *str) {
  int len = strlen(str);
  if (len < 2) {
    return len;
  }

  int maxLen = 1;
  for (int i = 0; i < len; i++) {
    int len1 = expandAroundCenter(str, i, i);
    int len2 = expandAroundCenter(str, i, i + 1);
    int resultLen = len1 > len2 ? len1 : len2;
    maxLen = resultLen > maxLen ? resultLen : maxLen;
  }

  return maxLen;
}

int main() {
  char str[2500];

  scanf("%2500s", str);

  int maxLen = longestPalindrome(str);
  printf("%d\n", maxLen);

  return 0;
}