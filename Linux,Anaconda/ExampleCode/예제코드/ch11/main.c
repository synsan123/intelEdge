#include <stdio.h>
#include "copy.h"

char line[MAXLINE];  	// �Է� ��
char longest[MAXLINE]; 	// ���� �� ��

/* �Է� �� ��� ���� �� ���� ����Ʈ�Ѵ�. */
main()
{
    int len;
    int max;

    max = 0;

    while (gets(line) != NULL) {
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
