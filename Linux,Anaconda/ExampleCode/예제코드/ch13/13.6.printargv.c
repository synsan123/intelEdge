#include <stdio.h>

/* ��� ����� �μ��� ����Ʈ�Ѵ�. */
int main(int argc, char *argv[])
{
    int      i;

    for (i = 0; i < argc; i++)            /* ��� ����� �μ� ����Ʈ  */
        printf("argv[%d]: %s \n", i, argv[i]);

    exit(0);
}