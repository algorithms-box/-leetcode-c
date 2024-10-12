#include <stdio.h>

int main()
{
    int input_tmp, sum = 0;
    while (scanf("%d", &input_tmp) != EOF)
    {
        sum += input_tmp;
        if (getchar() == '\n')
        {
            printf("%d\n", sum);
            sum = 0;
        }
    }

    return 0;
}
