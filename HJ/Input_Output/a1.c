#include<stdio.h>

int main()
{
    int a,b;
    while(scanf("%d %d",&a,&b)!=EOF)//要用while循环将scanf包裹，并且用EOF来判断是否到完成输入
    {
        printf("%d\n",a+b);//printf要加换行
    }
    return 0;
}
