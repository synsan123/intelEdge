#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* �ڽ� ���μ����� �����Ͽ� echo ��ɾ �����Ѵ�. */
int main( ) 
{    
	int pid, child, status;	

    printf("�θ� ���μ��� ����\n");
    pid = fork();
	if (pid == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr,"ù ��° ����");    
        exit(1);
    }
    else {
		child = wait(&status);
        printf("�ڽ� ���μ��� %d ��\n", child);
		printf("�θ� ���μ��� ��\n");
	}
}