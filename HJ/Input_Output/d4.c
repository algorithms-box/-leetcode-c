#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    while(n != 0){
        int tmp, sum = 0;
        for(int i=0; i<n; i++){
            scanf("%d", &tmp);
            sum += tmp;
        }

        printf("%d", sum);
        scanf("%d", &n);
    }

}
