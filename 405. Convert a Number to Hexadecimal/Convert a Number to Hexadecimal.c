#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 辅助函数，用于将整数转换为十六进制字符串
char *toHexString(int num) {
    char *hexString = (char *)malloc(
        9 * sizeof(char)); // 32位整数的最大十六进制表示为8个字符+1个'\0'
    if (num == 0) {
        strcpy(hexString, "0");
        return hexString;
    }

    int index = 0;
    char hexDigits[] = "0123456789abcdef";
    while (num > 0) {
        int remainder = num % 16;
        hexString[index++] = hexDigits[remainder];
        num /= 16;
    }
    hexString[index] = '\0';

    // 反转字符串
    int i = 0;
    int j = index - 1;
    while (i < j) {
        char temp = hexString[i];
        hexString[i] = hexString[j];
        hexString[j] = temp;
        i++;
        j--;
    }

    return hexString;
}

void test() {
    assert(strcmp(toHexString(26), "1a") == 0);
    assert(strcmp(toHexString(-1), "ffffffff") == 0);
    printf("All tests passed.\n");
}

int main() {
    test();
    return 0;
}