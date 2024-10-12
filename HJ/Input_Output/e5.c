#include <stdio.h>

int main() {
    int lines;
    scanf("%d", &lines);

    for(int i=0; i<lines; i++){
        int n, input_tmp, sum =0;
        scanf("%d", &n);

        for(int j=0; j<n; j++){
            scanf("%d", &input_tmp);
            sum += input_tmp;
        }
        printf("%d\n", sum);
    }

    return 0;
}
