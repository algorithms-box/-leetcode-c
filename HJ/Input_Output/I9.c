#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

int main()
{
    char s[100][100];
    int n = 0;
    while (scanf("%s", s[n]) != EOF)
    {
        n++;
        if (getchar() == '\n')
        {
            qsort(s, n, 100, cmp);
            for (int i = 0; i < n; i++)
            {
                printf("%s ", s[i]);
            }
            printf("\n");
            n = 0;
        }
    }

    return 0;
}
