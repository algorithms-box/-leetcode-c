#include <stdio.h>

int main(){
    int n, a, b;

    scanf("%d\n", &n);

    while (scanf("%d %d", &a, &b) != EOF && n>0) {
        n--;
        printf("%d\n", a+b);
    }

    return 0;
}
