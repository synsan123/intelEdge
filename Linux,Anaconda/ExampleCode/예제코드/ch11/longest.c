#include <stdio.h>
#include <string.h>
#define MAXLINE 100

char line[MAXLINE];    // �Է� ��
char longest[MAXLINE]; // ���� �� ��
void copy(char from[], char to[]);

/* �Էµ� �� ��� ���� �� ���� ����Ʈ�Ѵ�. */
int main()
{
    int len, max = 0;

    while (fgets(line, MAXLINE, stdin) != NULL) {
        len = strlen(line);
        if (len > max) {
            max = len;
            copy(line, longest);
        }
    }

    if (max > 0)   // �Է� ���� �־��ٸ�
       printf("%s", longest);

   return 0;
}

/*  from�� to�� ���� */
void copy(char from[], char to[])
{
   int i;

   i = 0;
   while ((to[i] = from[i]) != '\0')
       ++i;
}