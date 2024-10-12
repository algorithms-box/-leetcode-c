#include <stdio.h>

int main()
{
    int n, input_tmp = 0;
    while (scanf("%d", &n) != EOF)
    {
        int sum = 0;
        while (n--)
        {
            scanf("%d", &input_tmp);
            sum += input_tmp;
        }
        printf("%d\n", sum);
    }

    return 0;
}
