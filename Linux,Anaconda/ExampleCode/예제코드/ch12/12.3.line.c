#include <stdio.h>
#define MAXLINE 80
 
/* �ؽ�Ʈ ���Ͽ� �� ��ȣ �ٿ� ����Ʈ�Ѵ�. */
int main(int argc, char *argv[])
{
    FILE *fp;
    int line = 0;
    char buffer[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "����:line �����̸�\n");
        exit(1);
    }
 
    if ( (fp = fopen(argv[1],"r")) == NULL)
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(2);
    }

    while (fgets(buffer, MAXLINE, fp) != NULL) {  // �� �� �б�
        line++;
        printf("%3d %s", line, buffer);    // �ٹ�ȣ�� �Բ� ����Ʈ
    }
    exit(0);
 }
