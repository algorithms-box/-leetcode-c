#include <stdio.h>

int main(){
    int a, b;

    while (scanf("%d %d", &a, &b) != EOF && !(a == 0 && b == 0)) {
        printf("%d", a + b);
    }

    return 0;
}
