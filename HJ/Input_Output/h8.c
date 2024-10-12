#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cmp(const void *a, const void *b){
    return strcmp((const char *)a, (const char *)b);
}

int main()
{
    int n;
    scanf("%d", &n);

    char str[n][100];

    for (int i = 0; i < n; i++)
    {
        scanf("%s", str[i]);
    }

    qsort(str, n, 100, cmp);
    for (int i = 0; i < n; i++)
    {
        printf("%s ", str[i]);
    }

    return 0;
}
